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
	msg = to_chinese(arg) + " û���κ�������ʽ��\n";
	if (!arg)
		return notify_fail("ָ���ʽ: cskill <skill_name>��\n");

	//if (!objectp(skill = load_object(SKILL_D(arg))))
	if(file_size(SKILL_D(arg)+".c") < 1)
		return notify_fail("û�������ļ��ܣ�\n");
	//if(!wizardp(me) && !me->query_skill(arg, 1))
	//	return notify_fail("��û������ܣ�\n");
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
			msg = to_chinese(arg) + "������ʹ�ã�exert���У�\n\t";
			for( i = 0 ; i < j ; i++ )
			{
				msg = msg + "��" + replace_string(file[i], ".c", "") + "��";
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
			msg = to_chinese(arg) + "������ʹ�ã�perform���У�\n\t";
			for( i = 0 ; i < j ; i++ )
			{
				msg = msg + "��" + replace_string(file[i], ".c", "") + "��";
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
			msg = to_chinese(arg) + "������ʹ�ã�cast���У�\n\t";
			for( i = 0 ; i < j ; i++ )
			{
				msg = msg + "��" + replace_string(file[i], ".c", "") + "��";
			}
			msg = msg + "\n";
		}
	}
	else
	{
		msg = to_chinese(arg) + " û���κ�������ʽ��\n";
	}
	write(msg);
	return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ��cskill <skill_name>
HELP
        );
        return 1;
}
