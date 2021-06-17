// enchant.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int pts;

	if( !arg || (arg!="none" && arg!="max" && !sscanf(arg, "%d", pts)) )
		return notify_fail("ָ���ʽ��enchant <��������>|none|max\n");

	if ( arg == "none" )
		me->set("mana_factor", 0);
	else if ( arg == "max" ) {
		me->set("mana_factor", (int)me->query("max_mana")/20+1);
	} else if( pts > ((int)me->query("max_mana")/20+1) )
		return notify_fail("��ķ������㣬��������ôǿ��������\n");
    else if( pts < 0 )
    	return notify_fail("��������������������\n");
    else
		me->set("mana_factor", pts);
	write("Ok.\n");
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: enchant <��������>

���ָ�������趨ʹ��ħ������ʱҪ������������ħ�����õķ���ǿ�ȡ�
��������Խ�ߣ�ħ��������ɱ����ҲԽǿ��
enchant none ��ʾ�㲻ʹ�÷���
enchant max ��ʾ��ӷ��������

HELP
	);
	return 1;
}
