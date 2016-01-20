#include <libunwind.h>

static void debugInfo(FILE* out,const void* ip)
{

	char *debuginfo_path=NULL;

	Dwfl_Callbacks callbacks={
		.find_elf=dwfl_linux_proc_find_elf,
		.find_debuginfo=dwfl_standard_find_debuginfo,
		.debuginfo_path=&debuginfo_path,
	};

	Dwfl* dwfl=dwfl_begin(&callbacks);
	assert(dwfl!=NULL);

	assert(dwfl_linux_proc_report (dwfl, getpid())==0);
	assert(dwfl_report_end (dwfl, NULL, NULL)==0);

	Dwarf_Addr addr = (uintptr_t)ip;

	Dwfl_Module* module=dwfl_addrmodule (dwfl, addr);

	const char* function_name = dwfl_module_addrname(module, addr);

	fprintf(out,"%s(",function_name);

	Dwfl_Line *line=dwfl_getsrc (dwfl, addr);
	if(line!=NULL)
	{
		int nline;
		Dwarf_Addr addr;
		const char* filename=dwfl_lineinfo (line, &addr,&nline,NULL,NULL,NULL);
		fprintf(out,"%s:%d",strrchr(filename,'/')+1,nline);
	}
	else
	{
		fprintf(out,"%p",ip);
	}
}

static void __attribute__((noinline)) printStackTrace(FILE* out, int skip)
{

	unw_context_t uc;
	unw_getcontext(&uc);

	unw_cursor_t cursor;
	unw_init_local(&cursor, &uc);

	while(unw_step(&cursor)>0)
	{

		unw_word_t ip;
		unw_get_reg(&cursor, UNW_REG_IP, &ip);

		unw_word_t offset;
		char name[32];
		assert(unw_get_proc_name(&cursor, name,sizeof(name), &offset)==0);

		if(skip<=0)
		{
			fprintf(out,"\tat ");
			debugInfo(out,(void*)(ip-4));
			fprintf(out,")\n");
		}

		if(strcmp(name,"main")==0)
			break;

		skip--;

	}

}
