//Cracked by Roath
// suo.c ���־�

#include <ansi.h>

inherit SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, skill1, skill2, ap, dp, damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("lengquan-force",1);
        skill1 = me->query_skill("mace");
        skill2 = me->query_skill("dodge");
        
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "mace")
           return notify_fail("��û��ﵣ���ʲô�����˵ı�����\n");

        if( me->query("str") < 22 )
            return notify_fail("���������������, ����ʹ�á����й�һ����\n");
            
        if(me->query("family/family_name") != "������" )
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á����й�һ����\n");

        
        if( !(me->is_fighting() ))
            return notify_fail("�����й�һ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("wusi-mace", 1) < 100 )
                return notify_fail("�����˽ﵷ�������죬����ʹ�á�\n");
                                
        if( (int)me->query_skill("lengquan-force", 1) < 80 )
                return notify_fail("�����Ȫ�ķ�����Щ���\n");
        
        if (!objectp(weapon2 = target->query_temp("weapon")))
            return notify_fail("�Է�û��ʹ�ñ��������ò��ˡ����й�һ����\n");

	if (weapon2->query("no_get"))
		return notify_fail("�Է��ı��бȽ����⣬��᲻������\n");

        if( me->query("force") < 1000 )
                return notify_fail("��������������޷����á����й�һ����\n");


        msg = HIC "$N����"+weapon->name()+HIC"ӭ��һ�ܣ�б��һ����ʹ�������й�һ��������"+weapon->name()+HIC"��������$n"+HIC"��"+weapon2->name()+HIC"�ϡ�\n";
        message_vision(msg, me, target);
        
/*        damage = (int)me->query_skill("lengquan-force", 1);
        damage = damage +  (int)me->query_skill("wusi-mace", 1);
        damage = damage +  (int)me->query_skill("mace", 1);*/
                
        ap = skill + skill1 + skill2;
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1);
        if( dp < 1 )
            dp = 1;
        if( random(ap) > dp )
        {
            if(userp(me))
                 me->add("force",-500);
            msg = HIW"$n"+HIW"��ʱ����һ��ǿ������������Լ�����������";
            msg += weapon2->name();
            msg += HIW"���ַɳ�! \n"NOR;
//            msg += HIR"ͬʱ��Ѫ������ͷ���̲�ס�³�һ����Ѫ.\n"NOR;
            me->start_busy(1+random(2));
//            target->receive_damage("kee", damage);
//            target->start_busy( (int)me->query_skill("wusi-mace") / 20 + 1);
            weapon2->move(environment(me));
        }
        else
        {
            if(userp(me))
                 me->add("force",-250);
            msg = RED"$n"+RED"����������������" + weapon2->name()+
RED"бб˳��һ��һ����˻�����\n"NOR;
            me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}
