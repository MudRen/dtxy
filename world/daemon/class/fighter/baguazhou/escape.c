//Cracked by Roath
#include <ansi.h>

inherit SSERVER;

int scribe(object me,object ob)
{
	object seal;
        if(me->query("family/family_name")!="������")
                return notify_fail("�㲻�ǽ��������ӣ�����ʹ������ܣ�\n");

	if( (int)me->query("mana") < 100)
		return notify_fail("��ķ������㡣\n");
	if( (int)me->query("sen") < 100)
		return notify_fail("��ľ����޷����С�\n");
	

        if(me->query_temp("in_tiaozhan"))
        return notify_fail("�㻹����ս�У���ô���뿪�أ�\n");

	
	message_vision("$Nҧ����ָ���������ҷ�ֽ�ϻ��˼��¡�\n", me);
	
	destruct(ob);

	seteuid(getuid());
	seal=new("/d/jjf/obj/escape_seal");
	seal->move(me);

	//me->start_busy(2);
	return 1;
}
	
