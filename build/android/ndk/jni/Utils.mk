# Define functions
# reference: http://stackoverflow.com/questions/8980284/android-mk-include-all-cpp-files
#####################
# walk all files within given directory
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

# walk all *.c and *.cpp files within given direcory
define walksources
    $(filter %.cpp, %.c, $(call walk, $(1)))
endef
