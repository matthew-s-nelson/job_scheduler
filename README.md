# Job Schedule
## Description
A priority based job scheduler that allows for delayed execution of jobs. This job scheduler features:
- a thread pool
- condition variables
- a thread-safe priority queue
- a graceful shutdown

## Running the job scheduler
1. Clone the repository
2. Update the main.cpp file according to your needs.
   - The JobScheduler constructor accepts the number of threads that will be used in the thread pool.
   - Call the JobScheduler's schedule method to schedule a job passing in a lambda to execute for the job as well as delay (in milliseconds) and a priority (low # = high priority).
3. In the project's main directory (`job_scheduler`), run `make` to compile the .cpp files into the `job_scheduler` exectuable.
4. Run `./job_scheduler` to run the project.
5. Run `make clean` to clean up the compiled files.

## Run Tests
1. In the project's main direcotry (`job_scheduler`), run `make test` to compile the .cpp files to run the tests.
   - The tests run using Google Test which Homebrew can install using `brew install googletest`.
2. Run `./test_runner` to run the tests.
3. Run `make clean` to clean up the compiled files.
