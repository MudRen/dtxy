#include <ansi.h>
#include <skill.h>
inherit SSERVER;
int perform(object me, object target)
{
        int i, j, k, damage, delay;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʹ���޳�צ��\n");
		if(me->query("family/family_name") != "���޵ظ�")
                return notify_fail(HIG"���޳�צ��"+NOR"��ڤ�粻��֮�ܣ�\n");
        if(!me->is_fighting())
                return notify_fail("����û���ڴ�ܣ�\n");
        if((int)me->query("max_force") < 200 )
                return notify_fail("����ڹ�̫�\n");
        if((int)me->query("force") < 100 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
	if((int)me->query_skill("jinghun-zhang", 1) < 50)
        	return notify_fail("��ľ����Ƶȼ�����������ʹ����һ�У�\n");
	i=(int)me->query("combat_exp")/10000;
       	j=(int)target->query("combat_exp")/12000;
        k=(int)me->query_skill("jinghun-zhang");
        me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIB"\n$N����Ĭ����������޳��������޳�����ƫƫ������ײ����ϲŭ�޳����������ɣ���צ��"NOR,me,target);
	message_vision(HIB"\nһצץ��$n\n"NOR,me,target);
        if (random(i+j)>j/2) {
		damage=k+random(k);
		target->receive_damage("kee",damage);
		target->receive_wound("kee",damage/5);
		delay = 3 + random(3);
		if( me->query("lunhui_zhuanshi") > 4 )
			delay -= 1;
		target->start_busy(delay);
             	if (k>160) k=160;
		target->apply_condition("hell_zhua", (int)target->query_condition("hell_zhua")+2+k/20);
                COMBAT_D->report_status(target);
		message_vision(HIG"\n$n����һ�Σ�����������һ������ɫ��צ�ۣ�\n"NOR,me,target);
	}
	else message_vision(HIY"\n$n����һ�����㿪����һץ��\n"NOR,me,target);
	me->receive_damage("sen", 30);
        me->add("force", -100);
	me->receive_damage("kee", 30);
	if( me->query("lunhui_zhuanshi") > 4 )
		me->start_busy(1);
	else
    		me->start_busy(2);
	return 1;
}
