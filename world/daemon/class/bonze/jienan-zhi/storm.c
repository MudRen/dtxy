// ��������
// dream 7/17/97
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        if( !target ) target = offensive_target(me);
        if(me->query("family/family_name")!="�Ϻ�����ɽ")
                return notify_fail("�㲢�ǳ��Һ���,����ʹ������ܣ�\n");
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ���������꡹��\n");

        if((int)me->query("force") < 25+(int)me->query("force_factor") )
                return notify_fail("�������������\n");

        if((int)me->query("kee") < 100 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");

	if((int)me->query_skill("jienan-zhi", 1) <100)
		return notify_fail("��Ľ���ָ���𻹲�����\n");


        me->add("force", -25-(int)me->query("force_factor"));
        me->receive_damage("kee", 100);

        if( random(me->query("max_force")) < 50 ) {
                write("��⣬û�ɹ���\n");
                return 1;
        }


        COMBAT_D->attacking_perform(
                me, 
                        //attacker 
                target, 
                        //target
                (int)me->query_skill("jienan-zhi", 1), 
                        //level of skill used
                150, 
                        //success adjustment
                100, 
                        //damage adjustment
                "both", 
                        //damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
                HIC "\n$N���д����һ����ʩչ�����������꡹��˫��ʮָ���·��ɣ�����ǰ�������ƶ���\n
$nֻ���õ�����$N��Ӱ�ӣ�������֪����мܣ�������˵�����ˣ�\n\n" NOR,
                        //initial message
                HIC "���ʮָ���ʵʵȫ��������$n�����û��$n���˸�͸������\n" NOR, 
                        //success message
                HIC "����$n����һ���Ͷ��˿�����\n" NOR, 
                        //fail message
                HIC "���Ǳ�$n������һ�ƣ�ָ���������죡\n" NOR, 
                        //backfire initial message
                HIC "���ֻ�����꣡������$nʮָ����ȫ���۶ϣ�\n" NOR
                        //backfire hit message. note here $N and $n!!!
        );

me->start_busy(3);
return 5;
}
