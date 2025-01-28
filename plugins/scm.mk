ifeq (,$(shell guile-config --version 2>&1 | grep "Guile version 3"))

plugins/scm.so: plugins/scm.c
	$(CC) $(PLUGIN_FLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(EXTRA_CPPFLAGS) $(LDFLAGS) -o $@ $< $(PLUGIN_LIBS) $(LIBS)

else

plugins/scm.so: plugins/scm.c
	$(CC) $(PLUGIN_FLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(EXTRA_CPPFLAGS) $(LDFLAGS) $(shell guile-config compile) -DWITH_GUILE=1 -o $@ $< $(PLUGIN_LIBS) $(LIBS) $(shell guile-config link) 


endif


