#include <ansi.h>
#include <combat.h>
inherit SSERVER;
void remove_effect(object me, int amount);
int cast(object me, object target)
{
	if( (int)me->query("force") < 50 )
		return notify_fail("�������������\n");
        if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("�㲻����ɽ���ӣ�����ʹ������ܣ�\n");

	if( (int)me->query("mana") < 500 )
		return notify_fail("��ķ���������\n");

      message_vision(HIW"\n$N������֮��Ϊ���ã�����������Ϊ֮һ��\n"NOR,me);

	me->receive_curing("kee", 10 + (int)me->query_skill("force")/5 );
	me->receive_curing("sen", 10 + (int)me->query_skill("force")/5 );
	me->add("force", -50);
	me->add("spells", -500);
	me->set("force_factor", 0);
	me->set("mana_factor", 0);

	return 1;
}
