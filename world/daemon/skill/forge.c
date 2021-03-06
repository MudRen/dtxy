// forge.c

#include <ansi.h>

inherit SKILL;

string type() { return "forge"; }

string level_description(int level)
{
	int grade;
	string *level_desc = ({
		BLU "小修小补" NOR,
		BLU "马马乎乎" NOR,
		HIB "照猫画虎" NOR,
		HIB "精雕细刻" NOR,
		YEL "独具匠心" NOR,
		YEL "千金难求" NOR,
		CYN "举世罕有" NOR,
		HIW "巧夺天工" NOR
	});

	grade = level / 100;

	if( grade >= sizeof(level_desc) )
		grade = sizeof(level_desc)-1;
	return level_desc[grade];
}

