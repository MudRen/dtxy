// alchemy.c

#include <ansi.h>

inherit SKILL;

string type() { return "alchemy"; }

string level_description(int level)
{
	int grade;
	string *level_desc = ({
		BLU "火星乱溅" NOR,
		BLU "须发尽燃" NOR,
		HIB "偶而有成" NOR,
		HIB "十拿九稳" NOR,
		YEL "得心应手" NOR,
		YEL "点石成金" NOR,
		CYN "举世罕有" NOR,
		HIW "无人能及" NOR
	});

	grade = level / 100;

	if( grade >= sizeof(level_desc) )
		grade = sizeof(level_desc)-1;
	return level_desc[grade];
}

