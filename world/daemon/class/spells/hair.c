//lestat 2001

#include <ansi.h>
inherit SSERVER;

int cast(object me, object target)
{
        int invocation_time;
        object soldier;
		int num = me->query_skill("spells",1)/400;
		int i;
		if(!me->query("zspfm/zspfm_swk"))
                return notify_fail("�㻹û������������ܣ�\n");
        if( !me->is_fighting() )
                return notify_fail("�㶼����ս�����ٻ����Ӻ�����\n");
        if(me->query_skill("spells",1) <400)
                return notify_fail("��ķ����ȼ�������\n");  
        //invocation_time=30+(300-(int)me->query_skill("spells"));
        if(invocation_time<30) invocation_time=30;
        if((time()-me->query("last_invocation"))<invocation_time)
            return notify_fail("���ë���챻��ι��ˣ�\n");
        if( (int)me->query("mana") < 1000 )
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < 500 )
                return notify_fail("��ľ����޷����У�\n");

        message_vision(HIG"$N���¼���������͵ĺ�ë��������һ�ף����˿�������ë��Ȼ�������������\n"NOR, me);

        
		me->add("mana", -300);
        me->receive_damage("sen", 100);
        seteuid(getuid());
		for (i=0;i<num;i++) {
        soldier = new("/u/yekai/zspfm/hair_swk.c");
        soldier->move(environment(me));
        soldier->invocation(me);
    	soldier->set_temp("invoker",me);
		}
        me->set("last_invocation",time());
        me->start_busy(1);

        return 1;
}


