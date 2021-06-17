// alchemy.c

#include <ansi.h>

inherit SKILL;

string type() { return "alchemy"; }

string level_description(int level)
{
	int grade;
	string *level_desc = ({
		BLU "�����ҽ�" NOR,
		BLU "�뷢��ȼ" NOR,
		HIB "ż���г�" NOR,
		HIB "ʮ�þ���" NOR,
		YEL "����Ӧ��" NOR,
		YEL "��ʯ�ɽ�" NOR,
		CYN "��������" NOR,
		HIW "�����ܼ�" NOR
	});

	grade = level / 100;

	if( grade >= sizeof(level_desc) )
		grade = sizeof(level_desc)-1;
	return level_desc[grade];
}

