@echo off
echo Building Docker image...
docker build -t backtesting-engine .

if %ERRORLEVEL% neq 0 (
    echo Docker build failed!
    pause
    exit /b 1
)

echo Build successful!
echo Running Docker container...

REM Create logs directory if it doesn't exist
if not exist "logs" mkdir logs

REM Run the container with volume mount for logs
docker run --rm -v "%cd%/logs:/app/logs" backtesting-engine

if %ERRORLEVEL% neq 0 (
    echo Docker run failed!
    pause
    exit /b 1
)

echo Container execution completed!
echo Check the logs directory for output files.
pause
