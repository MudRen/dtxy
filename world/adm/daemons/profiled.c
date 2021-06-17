// profiled.c

#define MAX_ENTRIES 1000

mapping command_log;
int overflowed_log;

string sorting_by;

void create()
{
	seteuid(getuid());

	command_log = allocate_mapping(MAX_ENTRIES);
	overflowed_log = 0;
}

void log_command(string entry, int mem, int stime, int utime, int ecost)
{
	mapping command_entry = command_log[entry];
	if( !undefinedp(command_entry) ) {
		command_entry["count"] ++;
		command_entry["mem"] += mem;
		command_entry["stime"] += stime;
		command_entry["utime"] += utime;
		command_entry["ecost"] += ecost;
		if(command_entry["ecost1"] < ecost)
		  command_entry["ecost1"] = ecost;
		  //keep the maximum
	} else if( sizeof(command_log) <= MAX_ENTRIES ) {
		command_log[entry] = ([
			"count" : 1,
			"mem"   : mem,
			"stime" : stime,
			"utime" : utime,
			"ecost" : ecost,
			"ecost1" : ecost,
		]);
	} else
		overflowed_log++;
}

void make_profile(string sort_by)
{
	int i;
	string *entry, msg;

	entry = keys(command_log);
	sorting_by = sort_by;
	
	if( !stringp(sort_by) )	entry = sort_array(entry, 1);
	else 					entry = sort_array(entry, "sort_entry", this_object() );
	msg = 
"����           ����    ������         ϵͳʱ��  ʹ����ʱ��     ָ����\n";
// ecost is eval_cost.
	for(i=0; i<sizeof(entry); i++) {
	        int count=command_log[entry[i]]["count"];
		msg += sprintf("%-15s%-8d%-15d%-10d%-15d%-7d(%-8d)\n", entry[i],
			command_log[entry[i]]["count"],
			command_log[entry[i]]["mem"]/count,
			command_log[entry[i]]["stime"]/count,
			command_log[entry[i]]["utime"]/count,
			command_log[entry[i]]["ecost"]/count,
			command_log[entry[i]]["ecost1"]);
	}
	rm("/PROFILE");
	write_file("/PROFILE", msg);
}

int sort_entry(string entry1, string entry2)
{
	if( command_log[entry1][sorting_by] < command_log[entry2][sorting_by]) return -1;
	else if( command_log[entry1][sorting_by] > command_log[entry2][sorting_by]) return 0;
	return 0;
}
