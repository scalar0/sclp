set(CTEST_USE_LAUNCHERS TRUE)
set(CTEST_NIGHTLY_START_TIME 01:00:00 UTC) 

set(CTEST_SUBMIT_URL "https://my.cdash.org/submit.php?project=${CTEST_PROJECT_NAME}")
set(CTEST_DROP_SITE_CDASH TRUE)