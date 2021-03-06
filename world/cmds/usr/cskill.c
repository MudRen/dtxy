//modified by vikee
//2000.10
// perform.c
#include <ansi.h>
#include <skill.h>
#include "/cmds/std/valid_kill.h";

inherit F_CLEAN_UP;
int sort_skill(string file)
{
	int i;
	if ( file[<2..<1] != ".c" ) return 0;
	if ( !sscanf(file, "%*s.c") )  return 0;
	if ( sscanf(file, "%*s_noshow.c") )  return 0;
	i = strlen(file);
	while(i--){
		if( file[i] == '.' ) continue;
		if( file[i] < 'a' || file[i] > 'z' )
			return 0;
	}

	return 1;
}
int main(object me, string arg)
{
	string skill;
	string msg, directory,*file;
	int j = 0, i = 0;
	seteuid(getuid());
	msg = to_chinese(arg) + " 没有任何特殊招式。\n";
	if (!arg)
		return notify_fail("指令格式: cskill <skill_name>。\n");

	//if (!objectp(skill = load_object(SKILL_D(arg))))
	if(file_size(SKILL_D(arg)+".c") < 1)
		return notify_fail("没有这样的技能！\n");
	//if(!wizardp(me) && !me->query_skill(arg, 1))
	//	return notify_fail("你没有这项技能！\n");
	skill = SKILL_D(arg);
	if (stringp(directory = skill->exert_function_file("")))
	{
		file = get_dir(directory);
		if( sizeof(file) > 0)
		{
			file  = filter_array(file, (: sort_skill :) );
			j = sizeof(file);
		}
		if(j && j > 0)
		{
			msg = to_chinese(arg) + "的特殊使用（exert）有：\n\t";
			for( i = 0 ; i < j ; i++ )
			{
				msg = msg + "【" + replace_string(file[i], ".c", "") + "】";
			}
			msg = msg + "\n";
		}
	}
	else if (stringp(directory = skill->perform_action_file("")))
	{
		file = get_dir(directory);
		if( sizeof(file) > 0)
		{
			file  = filter_array(file, (: sort_skill :) );
			j = sizeof(file);
		}
		if(j && j > 0)
		{
			msg = to_chinese(arg) + "的特殊使用（perform）有：\n\t";
			for( i = 0 ; i < j ; i++ )
			{
				msg = msg + "【" + replace_string(file[i], ".c", "") + "】";
			}
			msg = msg + "\n";
		}
	}
	else if (stringp(directory = skill->cast_spell_file("")))
	{
		file = get_dir(directory);
		if( sizeof(file) > 0)
		{
			file  = filter_array(file, (: sort_skill :) );
			j = sizeof(file);
		}
		if(j && j > 0)
		{
			msg = to_chinese(arg) + "的特殊使用（cast）有：\n\t";
			for( i = 0 ; i < j ; i++ )
			{
				msg = msg + "【" + replace_string(file[i], ".c", "") + "】";
			}
			msg = msg + "\n";
		}
	}
	else
	{
		msg = to_chinese(arg) + " 没有任何特殊招式。\n";
	}
	write(msg);
	return 1;
}

int help (object me)
{
        write(@HELP
指令格式：cskill <skill_name>
HELP
        );
        return 1;
}
