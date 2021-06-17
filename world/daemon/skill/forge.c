// forge.c

#include <ansi.h>

inherit SKILL;

string type() { return "forge"; }

string level_description(int level)
{
	int grade;
	string *level_desc = ({
		BLU "С��С��" NOR,
		BLU "�������" NOR,
		HIB "��è����" NOR,
		HIB "����ϸ��" NOR,
		YEL "���߽���" NOR,
		YEL "ǧ������" NOR,
		CYN "��������" NOR,
		HIW "�ɶ��칤" NOR
	});

	grade = level / 100;

	if( grade >= sizeof(level_desc) )
		grade = sizeof(level_desc)-1;
	return level_desc[grade];
}

