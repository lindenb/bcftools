ifeq (,$(shell which guile-config 2>/dev/null))

plugins/scm.so:  plugins/scm.c
	$(CC) $(PLUGIN_FLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(EXTRA_CPPFLAGS) $(LDFLAGS) -o $@ $<  $(PLUGIN_LIBS) $(LIBS)


else


plugins/scm.so:  plugins/scm.c
	$(CC) $(PLUGIN_FLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(EXTRA_CPPFLAGS) $(LDFLAGS)  `guile-config compile` -DWITH_GUILE=1 -o $@  $< $(PLUGIN_LIBS) $(LIBS)  `guile-config link`


endif
