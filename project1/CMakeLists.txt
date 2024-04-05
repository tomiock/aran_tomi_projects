cmake_minimum_required(VERSION 3.10)

project(Project1)

enable_language(C)
enable_testing()

add_test(NAME UsageArgumentsEmpty COMMAND app)
set_tests_properties(UsageArgumentsEmpty
  PROPERTIES PASS_REGULAR_EXPRESSION "One arguments needed, no more no less. Execution finished."
  )

add_test(NAME UsageArgumentsZero COMMAND app 0)
set_tests_properties(UsageArgumentsZero
  PROPERTIES PASS_REGULAR_EXPRESSION "The argument must be a positive integer. Execution finished."
  )

add_test(NAME UsageArgumentsNegative COMMAND app -1)
set_tests_properties(UsageArgumentsNegative
  PROPERTIES PASS_REGULAR_EXPRESSION "The argument must be a positive integer. Execution finished."
  )

add_test(NAME UsageArgumentsOne COMMAND app 1)
set_tests_properties(UsageArgumentsOne
  PROPERTIES PASS_REGULAR_EXPRESSION "Starting..."
  )

add_test(NAME UsageArgumentsHundred COMMAND app 100)
set_tests_properties(UsageArgumentsHundred
  PROPERTIES PASS_REGULAR_EXPRESSION "Starting..."
  )

add_test(NAME UsageArgumentsLarge COMMAND app 10000000000000000000000)
set_tests_properties(UsageArgumentsLarge
  PROPERTIES PASS_REGULAR_EXPRESSION "Too large of a number, does not fit in type `int`. Execution finished."
  )

add_executable(app main.c)

