#ifndef TESTCONFIGURATION_H
#define TESTCONFIGURATION_H
// Uncomment the below define for unit test purposes
//#define LOCAL_TEST_MODE

#ifdef LOCAL_TEST_MODE
#define TEST_MODE
#endif
#ifdef REMOTE_TEST_MODE
#define TEST_MODE
#endif
#endif // TESTCONFIGURATION_H
