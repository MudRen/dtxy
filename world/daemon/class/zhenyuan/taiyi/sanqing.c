//lestat 2001

#include <ansi.h>
inherit SSERVER;

int cast(object me, object target)
{
        int invocation_time;
        object soldier;

        if( !me->is_fighting() )
                return notify_fail("ֻ��ս���в��ܻ����塣\n");
//        if(me->query("family/family_name")!="��ׯ��")
//                return notify_fail("�㲻��һ�������壡\n");
                if(me->query_skill("taiyi", 1) <80)
                return notify_fail("����������Ϊ�����ܻ����塣\n");  
        invocation_time=60+(300-(int)me->query_skill("spells"));
        if(invocation_time<60) invocation_time=60;
        if( me->query("lunhui_zhuanshi") )
		invocation_time -= me->query("lunhui_zhuanshi") * 6;
        if((time()-me->query("last_invocation"))<invocation_time)
            return notify_fail("��ջ������壬�������㣡\n");
//                if((int)me->query("daoxing") > 3456000) 
//            return notify_fail("�㻹û����������,���ܻ����壡\n");
        if( (int)me->query("mana") < 1000 )
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < 500 )
                return notify_fail("��ľ����޷����У�\n");

        message_vision(HIG"$N����Ȧ�������ѷ���һ�ƣ�ֻ������������������Ϊ���塣\n"NOR, me);

        if( random(me->query("max_mana")) < 500 ) {
                message("vision", "����ʲôҲû�з�����\n",
environment(me));
                return 1;
        }
	me->add("mana", -300);
        me->receive_damage("sen", 100);
        seteuid(getuid());
        soldier = new("/obj/npc/dao1");
        soldier->move(environment(me));
        soldier->invocation(me);
    	soldier->set_temp("invoker",me);
        me->set("last_invocation",time());
        me->start_busy(1);
                if(me->query_skill("taiyi", 1) > 120)
        call_out("sanqing2", 1, me, target);   

        return 1;
}

int sanqing2(object me, object target)
{
	object soldier;
        seteuid(getuid());
        if(!objectp(me))
        	return 0;
        if( (int)me->query("mana") < 300 )
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < 100 )
                return notify_fail("��ľ����޷����У�\n");
        me->add("mana", -300);
        me->receive_damage("sen", 100);
        soldier = new("/obj/npc/dao2");
        soldier->move(environment(me));
        soldier->invocation(me);
    	soldier->set_temp("invoker",me);
                if(me->query_skill("taiyi", 1) > 150)
        call_out("sanqing3", 1, me, target);   

        return 1;
}
int sanqing3(object me, object target)
{
	object soldier;
	int invocation_time;
        seteuid(getuid());
        if(!objectp(me))
        	return 0;
        if( (int)me->query("mana") < 300 )
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < 100 )
                return notify_fail("��ľ����޷����У�\n");
        me->add("mana", -300);
        me->receive_damage("sen", 100);
        soldier = new("/obj/npc/dao3");
        soldier->move(environment(me));
        soldier->invocation(me);
    	soldier->set_temp("invoker",me);
//        me->set("last_invocation",time());
        return 1;
}

