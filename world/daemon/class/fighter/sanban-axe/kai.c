// ����ٵ�
// kugu 2006 ������
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        int ap,dp,delay;
        object weapon;
        int cd = 10;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ��"+HIM"������ٵء�"+NOR"��\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("�������������\n");
	if(!me->is_fighting(target))
                return notify_fail("��û����ս���У�\n");
        if((int)me->query("kee") < 1000 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
	if( !me->query("kai_known") )
                return notify_fail("��û�еõ�����ٵصĿھ���\n");
        if((int)me->query_skill("sanban-axe", 1) <200)
                return notify_fail("������������𻹲�����\n");
        if((int)me->query_skill("lengquan-force", 1) <200)
                return notify_fail("�����Ȫ�񹦼��𻹲�����\n");
        if(me->query("family/family_name") != "������")
                return notify_fail(HIR"������ٵء�"+NOR"�ǽ���������֮�ܣ�\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
	if( time()-(int)me->query_temp("kai_end") < cd )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->start_busy(1);
	ap = me->query("combat_exp")/10000;
	dp = target->query("combat_exp")/12000;
	delay = 3 + random(1+me->query("kai_known"));
	weapon = me->query_temp("weapon");
        message_vision(HIC"\n$N�Ӷ�"+ weapon->name() +HIC"ն��$n��ࡣ\n"NOR,me,target);
        message_vision(CYN"$n������������æ������\n" NOR,me,target);
        message_vision(HIC"\n$N��"+ weapon->name() +HIC"�Ữ����$n�Ҳ�����\n"NOR,me,target);
        if( me->query("kai_known") > 1 )
        {
        	message_vision(CYN"$n�����ŵأ���Ҫ����Ծ��\n" NOR,me,target);
        	message_vision(HIC"\n$N����һ��"+ weapon->name() +HIC"��$nͷ������������\n"NOR,me,target);
        }
        if( me->query("kai_known") > 2 )
        {
        	message_vision(CYN"$n�ִ��У��Ÿ�ǰ����Ҫ��Ծ��\n" NOR,me,target);
        	message_vision(HIC"\n$N����һ�죬"+ weapon->name() +HIC"����$n�ĺ�ն�¡�\n"NOR,me,target);
        }
        message_vision(HIC"$N��"+ chinese_number(1+me->query("kai_known")) +"��������ʵ���Ѿ�������$N������"+ weapon->name() +HIC"ק�ء�\n"NOR,me,target);
        if( me->query("gender") == "Ů��" )
                message_vision(HIC"$N��Хһ����"+ weapon->name() +HIC"�Ϸ�������ɱ����$N��۲�����$nӭ���������һ����\n"NOR,me,target);
        else
        	message_vision(HIC"$N����һ����"+ weapon->name() +HIC"��ɱ��֮����ʢ��$N��۲�����$nӭ���������һ����\n"NOR,me,target);
        message_vision(CYN"$n��$N�������壬������$N��â������������������·��\n\n" NOR,me,target);
        if( me->query("kai_known") < 2 && random(ap) < dp/3 )
        {
        	message_vision(CYN"$n�����ŵأ����Ծ�𣬶㿪��$N�Ĺ�����\n" NOR,me,target);
        	return 1;
        }
        if( me->query("kai_known") < 3 && random(ap) < dp/4 )
        {
        	message_vision(CYN"$n����һ�ܣ����ƽŸ�ǰ�ţ����Ծ�����㿪��$N�Ĺ�����\n" NOR,me,target);
        	return 1;
        }
        if( random(ap) < dp/5 )
        {
        	message_vision(CYN"$n���һ����ʹ�����ж��е����ݴӵ��¶��ߣ��㿪��$N�Ĺ�����\n" NOR,me,target);
        	return 1;
        }
        message_vision(HIC"$n�ۼ���ͷ��Х���������������·���ˣ�ֻ�ñ�Ŀ������\n" NOR,me,target);
        target->start_busy(delay);
        me->set_temp("kai_end",time());
        return 1;
}
