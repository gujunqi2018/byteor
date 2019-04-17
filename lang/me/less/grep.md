# grep

### Search the pattern

> grep -r -w -n DECLARE_MUTEX /home/esc/linux/

```
[esc@thinkpad esc]$ grep -r -w -n DECLARE_MUTEX /home/esc/linux/
/home/esc/linux/arch/ia64/sn/kernel/sn2/sn_hwperf.c:53:static DECLARE_MUTEX(sn_hwperf_init_mutex);
/home/esc/linux/arch/x86/kernel/cpu/mcheck/mce_64.c:567:   static DECLARE_MUTEX(mce_read_sem);
/home/esc/linux/arch/mips/lasat/picvue.c:25:DECLARE_MUTEX(pvc_sem);
/home/esc/linux/arch/um/drivers/mconsole_kern.c:361:static DECLARE_MUTEX(plug_mem_mutex);
/home/esc/linux/arch/um/drivers/port_kern.c:123:static DECLARE_MUTEX(ports_sem);
/home/esc/linux/arch/arm/mach-omap1/board-nokia770.c:206:static DECLARE_MUTEX(audio_pwr_sem);
/home/esc/linux/arch/arm/mach-lh7a40x/clocks.c:83:static DECLARE_MUTEX(clocks_sem);
/home/esc/linux/drivers/watchdog/s3c2410_wdt.c:93:static DECLARE_MUTEX(open_lock);
/home/esc/linux/drivers/scsi/qla2xxx/qla_os.c:2785:static DECLARE_MUTEX(qla_fw_lock);
/home/esc/linux/drivers/macintosh/adb.c:86:static DECLARE_MUTEX(adb_probe_mutex);
/home/esc/linux/drivers/macintosh/adb.c:121:static DECLARE_MUTEX(adb_handler_sem);
/home/esc/linux/drivers/macintosh/therm_pm72.c:171:static DECLARE_MUTEX(driver_lock);
```