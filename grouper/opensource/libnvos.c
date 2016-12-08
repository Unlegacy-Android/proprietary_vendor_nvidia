void *NvOsAllocLeak(size_t size)
{
    return malloc(size);
}

uint32_t NvOsAtomicCompareExchange32(uint32_t *pTarget, uint32_t OldValue,
    uint32_t NewValue)
{
    return atomic_cmpxchg((atomic_t *)pTarget, OldValue, NewValue);
}

uint32_t NvOsAtomicExchange32(uint32_t *pTarget, uint32_t Value)
{
    return atomic_xchg((atomic_t *)pTarget, Value);
}

uint32_t NvOsAtomicExchangeAdd32(uint32_t *pTarget, uint32_t Value)
{
    uint32_t new;
    new = atomic_add_return(Value, (atomic_t *)pTarget );
    return new + (-Value);
}

// NvOsBootArgGet                    00006F34
// NvOsBreakPoint                    0000720C
// NvOsCallstackCreate               00006F8C
// NvOsCallstackDestroy              00007008
// NvOsCallstackDump                 00007094
// NvOsCallstackGetFrame             0000703C
// NvOsCallstackGetHeight            00007030
// NvOsCallstackHash                 00007294

int32_t NvOsCheckpoint()
{
    return INT32_MAX;
}

// NvOsClosedir                      000045D0

int32_t NvOsConditionBroadcast(pthread_cond_t *cond)
{
    if (!cond)
        return -EINVAL;

    return pthread_cond_broadcast(cond);
}

int32_t NvOsConditionCreate(pthread_cond_t *cond)
{
    int err;

    cond = NvOsAllocLeak(4);

    if (!cond)
        return -ENOMEM;

    err = pthread_cond_init(cond, 0);
    if (err) {
        NvOsFreeLeak(cond);
        return err;
    }

    return 0;
}

int32_t NvOsConditionDestroy(pthread_cond_t *cond)
{
    int err;

    err = pthread_cond_destroy(cond);
    if (err)
        return err;

    NvOsFreeLeak(cond);

    return 0;
}

int32_t NvOsConditionSignal(pthread_cond_t *cond)
{
    return pthread_cond_signal(cond);
}

int32_t NvOsConditionWait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    return pthread_cond_wait(cond, mutex);
}

int32_t NvOsConditionWaitTimeout(pthread_cond_t *cond, pthread_mutex_t *mutex,
    uint32_t timeInMs)
{
    struct timespec timeToWait;
    struct timeval now;

    gettimeofday(&now, NULL);

    timeToWait.tv_sec = now.tv_sec + 5;
    timeToWait.tv_nsec = (now.tv_usec + 1000UL * timeInMs) * 1000UL;

    return pthread_cond_timedwait(cond, mutex, &timeToWait);
}

// NvOsConfigGetState                00004D24
// NvOsConfigQueryState              00004D60
// NvOsConfigSetState                00004CF0

int32_t NvOsCopyOut(void *destination, const void *source, size_t num)
{
  NvOsMemcpy(destination, source, num);
  return 0;
}

int32_t NvOsDebugPrintf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    LOG_PRI_VA(ANDROID_LOG_DEBUG, "NvOsDebugPrintf", format, ap);
    va_end(ap);

    return 0;
}

int32_t NvOsDebugVPrintf(const char *format, va_list ap)
{
    LOG_PRI_VA(ANDROID_LOG_DEBUG, "NvOsDebugVPrintf", format, ap);

    return 0;
}

// NvOsDumpToDebugPrintf             0000339C

int32_t NvOsExecAlloc(int fd)
{
    static int fd = 0;
    int ret;

    if (!fd) {
        fd = open("/dev/zero", O_RDWR);
        if (fd < 0) {
            NvOsDebugPrintf("%s: error %d opening /dev/zero\n", __func__, errno);
            return 0;
        }

    }

    ret = mmap(0, fd);
    if (ret == MAP_FAILED) {
        NvOsDebugPrintf("%s: mmap error %d\n", __func__, errno);
        ret = 0;
    }

    return ret;
}

void NvOsFclose(FILE *file)
{
    fclose(handle);
}

int32_t NvOsFflush(FILE *file)
{
    return fflush(file);
}

int32_t NvOsFgetc(FILE *file)
{
    return fgetc(file);
}

int32_t NvOsFlock(int fd, int operation)
{
    return flock(fd, operation);
}

int32_t NvOsFopen(const char *path, uint32_t flags, FILE *file)
{
    file = fopen(path, flags);

    if (!file)
        return 1;

    return 0;
}

int32_t NvOsFprintf(FILE *file, const char *format, ...)
{
    va_list ap;
    int err;

    va_start(ap, format);

    err = vfprintf(fp, format, ap);
    if (err < 0)
        return err;

    va_end(ap);

    return 0;
}

int32_t NvOsFread(FILE *file, void *ptr, size_t size, size_t *bytes)
{
    int ret;

    ret = fread(ptr, size, bytes, file);
    if (bytes != ret)
        return ret;

    return 0;
}

void NvOsFreeLeak(void *ptr)
{
    if (ptr)
        free(ptr);
}

int NvOsFremove(const char *path)
{
    return unlink(path);
}

int NvOsFseek(FILE *file, off64_t offset, int whence)
{
    int err;

    err = lseek64(file, offset, whence);

    if (err == -1)
        return 1;

    return 0;
}

int NvOsFstat(FILE *file, struct stat *stat)
{
    return fstat(file, stat);
}

int NvOsFtell(FILE *file, off64_t *position)
{
    position = lseek64(file, 0, SEEK_CUR);
    if (position == -1)
        return 1;

    return 0;
}

int NvOsFwrite(FILE *fd, const void *ptr, size_t size)
{
    int err;
    err = fwrite(ptr, 1, size, fd);
    if (err != count)
        return err;

    return 0;
}

NvError NvOsGetConfigString(const char *name, char *value, NvU32 size)
{
    return NvError_NotImplemented;
}

// NvOsGetConfigString               00004AF4
// NvOsGetConfigU32                  00004B24
// NvOsGetOsInformation              00006F58
// NvOsGetProcessInfo                000072AC
// NvOsGetResTrackerStat             00003390
// NvOsGetSystemTime                 00006D30

uint32_t NvOsGetTimeMS(void)
{
    struct timespec spec;

    clock_gettime(CLOCK_MONOTONIC, &spec);

    return round(spec.tv_nsec / 1000000);
}

uint32_t NvOsGetTimeUS(void)
{
    struct timespec spec;

    clock_gettime(CLOCK_MONOTONIC, &spec);

    return round(spec.tv_nsec / 1000);
}

void NvOsInstrCacheInvalidateRange(void *start, uint32_t length)
{
    flush_icache_range((unsigned long) start,
        (unsigned long) start+length);
}

NvOsInterruptDone                 00006EB8
NvOsInterruptEnable               00006E70
NvOsInterruptMask                 00006EF0
NvOsInterruptPriorityThreadCreate 00003624
NvOsInterruptRegister             00006DB8
NvOsInterruptUnregister           00006E38
NvOsIntrMutexCreate               00005BE4
NvOsIntrMutexDestroy              00005BC8
NvOsIntrMutexLock                 00005C18
NvOsIntrMutexUnlock               00005C1C
NvOsIoctl                         00005220
NvOsLibraryGetSymbol              00005870
NvOsLibraryLoad                   000057A4
NvOsLibraryUnload                 00005874
NvOsMemcmp                        00005144
NvOsMemcpy                        00005090
NvOsMemmove                       0000514C
NvOsMemset                        00005148
NvOsMkdir                         000045F8
NvOsMutexCreate                   00003404
NvOsMutexDestroy                  0000346C
NvOsMutexLock                     0000342C
NvOsMutexUnlock                   0000344C
NvOsOpendir                       00004590
NvOsPageAddress                   0000579C
NvOsPhysicalMemMap                00005684
NvOsPhysicalMemUnmap              00005758
NvOsProfileApertureSizes          00006F28
NvOsReaddir                       000045B0
NvOsReallocLeak                   000033FC
NvOsResourceInfo                  00003FEC
NvOsSemaphoreClone                00003518
NvOsSemaphoreCreate               00003494
NvOsSemaphoreDestroy              00003538
NvOsSemaphoreSignal               000034F8
NvOsSemaphoreUnmarshal            00005F20
NvOsSemaphoreWait                 000034B4
NvOsSemaphoreWaitTimeout          000034D8
NvOsSetConfigString               00004BF8
NvOsSetConfigU32                  00004C20
NvOsSetFileHooks                  00004300
NvOsSetSystemTime                 00003384
NvOsSharedMemAlloc                000054FC
NvOsSharedMemFree                 000055E0
NvOsSharedMemMap                  00005580
NvOsSharedMemUnmap                000054F0
NvOsShowError                     00008AA4
NvOsSleepMS                       000036B4
NvOsSnprintf                      00004E70
NvOsStat                          00004490
NvOsStrGetSystemCodePage          00005080
NvOsStrcmp                        00005088
NvOsStrcpy                        00005074
NvOsStrlen                        0000507C
NvOsStrncmp                       0000508C
NvOsStrncpy                       00005078
NvOsThreadCreate                  00003600
NvOsThreadGetAffinity             000060D0
NvOsThreadJoin                    00003648
NvOsThreadMode                    00004044
NvOsThreadSetAffinity             00006094
NvOsThreadSetLowPriority          00003670
NvOsThreadYield                   00003694
NvOsTlsAddTerminator              000035E0
NvOsTlsAlloc                      00003560
NvOsTlsFree                       00003580
NvOsTlsGet                        000035A0
NvOsTlsSet                        000035C0
NvOsTraceLogPrintf                00004214
NvOsVerifyHeap                    0000338C
NvOsVfprintf                      00006B08
NvOsVsnprintf                     00004E9C
NvOsWaitUS                        00005A2C
NvUHashClear                      00008D58
NvUHashContains                   00008CC0
NvUHashDeinit                     00008D74
NvUHashGet                        00008CE2
NvUHashInit                       00008CA8
NvUHashInsert                     00008D78
NvUHashNextEntry                  00008F6A
NvUHashRemove                     00008E94
NvUHashRemoveNoRehash             00008E38
NvUHashReplace                    00008EE8
NvUHashSearch                     00008D12
NvULowestBitSet                   00008A64
NvUScalarCompare                  0000913C
NvUScalarHash                     000090DC
NvUStrCompare                     000090CC
NvUStrHash                        00008FA8
NvUStrlConvertCodePage            000088FC
NvUStrncat                        0000889E
NvUStrstr                         000088C2
NvUStrtol                         0000889A
NvUStrtoul                        00008892
NvUStrtoull                       000087D4