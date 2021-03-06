// enchant.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int pts;

	if( !arg || (arg!="none" && arg!="max" && !sscanf(arg, "%d", pts)) )
		return notify_fail("指令格式：enchant <法力点数>|none|max\n");

	if ( arg == "none" )
		me->set("mana_factor", 0);
	else if ( arg == "max" ) {
		me->set("mana_factor", (int)me->query("max_mana")/20+1);
	} else if( pts > ((int)me->query("max_mana")/20+1) )
		return notify_fail("你的法力不足，发不出那么强的威力。\n");
    else if( pts < 0 )
    	return notify_fail("法力点数必须是正数。\n");
    else
		me->set("mana_factor", pts);
	write("Ok.\n");
	return 1;
}

int help (object me)
{
	write(@HELP
指令格式: enchant <法力点数>

这个指令让你设定使用魔法武器时要用来导引武器魔力所用的法力强度。
法力点数越高，魔法武器的杀伤力也越强。
enchant none 表示你不使用法力
enchant max 表示你加法力到最大

HELP
	);
	return 1;
}
