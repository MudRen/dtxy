//Cracked by Roath
// duo.c ���������
//pudding 99.12
#include <ansi.h>

inherit SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, dp, damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        //if( (int)me->query_temp("duo") )
        //        return notify_fail("���Ѿ��ڶ���˵ı����ˡ�\n");
        skill = me->query_skill("yinfeng-zhua",1);

        if( !(me->is_fighting(target) ))
                return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("�������֡�\n");
         if(me->query("family/family_name")!="�ݿ�ɽ�޵׶�")
             return notify_fail("�㲻���������ģ������ÿ��������\n");
        if (!objectp(weapon2 = target->query_temp("weapon")))
           return notify_fail("�Է�û�б��У��㲻�õ��ġ�\n");
		if (weapon2->query("no_get"))
			return notify_fail("�Է��ı��бȽ����⣬��᲻������\n");
//        if( skill < 50)
        if( skill < 180)
                return notify_fail("�������צ�ȼ�����, ���ܿ�������У�\n");
//                return notify_fail("�����������ʱ���,�ȴ�������\n");

        if( me->query("force") < 1000 )
                return notify_fail("��������������޷���������У�\n");
 	if( time()-(int)me->query_temp("duo_end") < 5 )
 		return notify_fail("��������Ϣ��˳��\n");
 	me->set_temp("duo_end",time());
        msg = CYN "$N�����Ϣ������ʩչ��������еľ���. \n";
        message_vision(msg, me);

        dp = target->query_skill("parry") / 3;
        if( dp < 1 )
                dp = 1;
        if( random(skill) > dp )
        {
                //if(userp(me))
                me->add("force",-skill);
                msg = "$NͻȻ�ֱ۱���, $n��ʱ������ǰһ��������һ�飬���б������ֶ�����\n" NOR;
                //target->start_busy(2);
                if ( me->is_manmade_npc() ) {
                    weapon2->move(environment(me));
                } else {
                    weapon2->move(me);
                }
                //me->start_busy(random(2));
        }
        else
        {
               	me->add("force",-100);
                msg = "����$n�Ŀ�����$N����ͼ�����̲�ȡ���ƣ�ʹ$Nû�ܶ��±��С�\n"NOR;
        }
        me->start_busy(1+random(2));
        message_vision(msg, me, target);

        return 1;
}
