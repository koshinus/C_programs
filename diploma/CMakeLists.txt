cmake_minimum_required(VERSION 3.5)

# In src folder is the code of this server, including tests for it
# In test folder is the calling of tests with Google Test library
# Server compiled with GCC (11 standard), and GTests with G++ (14 standard)

add_subdirectory(src)
add_subdirectory(client)
#add_subdirectory(test)
