# projectify

![🛠 Tech Stack](https://go-skill-icons.vercel.app/api/icons?i=cpp,cmake,postgresql,docker)

> [!IMPORTANT]
> The project is still in its early stages of development and many features are missing. Stay tuned for updates!

<pre>
                    _              _    _   __
                   (_)            | |  (_) / _|
 _ __   _ __  ___   _   ___   ___ | |_  _ | |_  _   _
| '_ \ | '__|/ _ \ | | / _ \ / __|| __|| ||  _|| | | |
| |_) || |  | (_) || ||  __/| (__ | |_ | || |  | |_| |
| .__/ |_|   \___/ | | \___| \___| \__||_||_|   \__, |
| |               _/ |                           __/ |
|_|              |__/                           |___/
</pre>

> Your go-to solution for managing projects efficiently. Organize projects smarter, achieve results faster.

## Index

1. [Overview](#overview)
2. [Project Architecture](#project-architecture)
3. [Getting started](#getting-started)

   - [Backend and database setup](#backend-and-database-setup)
   - [Frontend-cli setup](#frontend-cli-setup)

4. [Some screenshots](#some-screenshots)

## Overview

🚀 **projectify** is a simple and intuitive project management tool that helps you organize your work efficiently.

✅ Create projects, add tasks, and attach relevant links—all in one streamlined space.

📈 Stay on top of your workflow, track progress effortlessly, and bring your ideas to life with speed and precision.

## Project Architecture

projectify is composed of three big parts:

- Database: PostgreSQL for storing project data and user information.
- Backend: a RESTful API server written in C++ that interacts with the database and manages project logic. Uses [Crow](https://github.com/CrowCpp/Crow) as web framework and [taopq](https://github.com/taocpp/taopq) for database operations.
- Frontend-cli: a terminal application written in C++ with [FTXUI](https://github.com/ArthurSonzogni/FTXUI) in order to create an intuitive user interface on the command line. Uses [glaze](https://github.com/stephenberry/glaze) to handle JSON data and [cpp-httplib](https://github.com/yhirose/cpp-httplib) for HTTP requests.

**🌐 A web-based frontend is on the schedule. Stay tuned for updates!**

The database and the backend run on top of Docker containers based on PostgreSQL official image for the database and a lightweight Alpine image for the backend, ensuring a consistent and reproducible environment.

Both backend and frontend-cli use CMake as build system.

![architecture-schema](screenshots/architecture-schema.png)

## Getting started

To get started with projectify, follow these steps:

📥 Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/landiluigi746/projectify.git
cd projectify
```

### Backend and database setup

**Skip this part if you don't want to run them yourself**

1. ⚙️ Create a ```.env``` file with the variables required for the project:
```bash
# Backend config
PORT=8080
BUILD_TYPE=Release
REQUESTS_PER_MINUTE=15
JWT_SECRET=secret_key
JWT_DURATION=3600 # seconds

# Database config
POSTGRES_USER=username
POSTGRES_PASSWORD=password
POSTGRES_DB=projectify-db
POSTGRES_HOST=projectify-db
POSTGRES_PORT=5432
```

2. 🏗️ Build and start the Docker containers:
```bash
docker compose up --build -d
```

3. ⚙ Set an system env variable with your backend URL

Bash:
```bash
export PROJECTIFY_BACKEND_URL=localhost:8000
```

Windows CMD:
```cmd
set PROJECTIFY_BACKEND_URL=localhost:8000
```

### Frontend-cli setup

🖥️ Compile and run the cli frontend:

**Windows**:

It's highly recommended to use Visual Studio 2022. Open the frontend-cli folder directly in VS, let it generate CMake files and then compile the app.

**Linux**:
```bash
cd frontend-cli
# if you want to build in a different build type, change this value
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# if you want, you can use a parallel build
# and specify the number of jobs to run in parallel (use $(nproc) to use all availableprocessing units)
cmake --build build --target projectify-cli --parallel 4
./bin/projectify-cli
```

## Some screenshots
| ![frontend-cli1](screenshots/frontend-cli1.png) | ![frontend-cli2](screenshots/frontend-cli2.png) |
|-|-|
