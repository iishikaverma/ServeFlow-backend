# ---------- Build stage ----------
FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake g++ make curl zip unzip tar pkg-config ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# vcpkg (dependencies are resolved from vcpkg.json in manifest mode)
RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git /opt/vcpkg \
    && /opt/vcpkg/bootstrap-vcpkg.sh -disableMetrics
ENV VCPKG_ROOT=/opt/vcpkg

WORKDIR /app
COPY vcpkg.json CMakeLists.txt ./
COPY include ./include
COPY src ./src
COPY data ./data

RUN cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
    && cmake --build build --target serveflow_api

# ---------- Runtime stage ----------
FROM ubuntu:24.04 AS runtime

WORKDIR /app
COPY --from=build /app/build/serveflow_api ./serveflow_api
COPY --from=build /app/data ./data

# Render injects $PORT; the server reads it (defaults to 18080 locally).
ENV PORT=10000
EXPOSE 10000

CMD ["./serveflow_api"]
