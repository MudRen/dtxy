/*
	����˼��ɱʽ����������ɽ������ӯ�䣬��Ŀ���
���������۾��ˣ���һʽ�Գ�˼�⾳�����������е�Ǳ�ܣ��������Ҿ�ɱ�� 

	�����ŭʽ�����𷽲���������ǧ�����б��Թ����Թ��ӯ��
���ŭʽ�����ʱӯ����Թ��ת��ɱ�����ٽ�ɱ��һ��й����ȡ�������� 

	���ϳ�����ʽ��������ǳЦ����գ��ϳ�����֪Ϊ˭��
��������ĳ�˼�����������ı��룬���ڻ�������ϳ������һ���� 
��ôɽ�˺��ģ���ô������ģ����ǵֲ�סһ�������������ҹ�λء� 
���������ڣ������˶ϳ��� 

*/
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,damage,ap,dp;
        object weapon;
        int cd = 10;
       	if( !wizardp(me) && (string)me->query("family/family_name") != "���޵ظ�" )
                return notify_fail("[������ʽ]��ڤ�粻��֮�ܣ�\n");
        if( !me->query("jingtian_known") )
                return notify_fail("�㻹û��ѧ��[������ʽ]��\n");
        extra = me->query_skill("zhuihun-sword",1);
	if( me->query("force") < 1800 ) 
		return notify_fail("���״̬���ã��޷�ʹ��[ͼ��ذ��]��\n");
        if ( extra < 200) 
        	return notify_fail("���׷�꽣�����𻹲�����ʹ����һ�л���һ���Ѷȣ�\n");
        if( (int)me->query_skill("sword", 1) < 200)
                return notify_fail("��Ľ�����Ƿȱ�������޷�����Ӧ�֡�\n");
        if( (int)me->query_skill("tonsillit", 1) < 200)
                return notify_fail("����������ȼ�̫�͡�\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�۾�����ʽ��ֻ����ս����ʹ�á�\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
       	if( time()-me->query_temp("jingtian_end") < cd ) 
       		return notify_fail("������ʽ�����õ���ôƵ����\n");         
        me->set_temp("jingtian_end",time());
        weapon = me->query_temp("weapon");
        ap = me->query_skill("tonsillit",1);
        dp = target->query_skill("dodge",1);
        msg = HIB"\n$Nŭ��һ������ز��ʣ�������Ϊۻ��������Թŭ֮���籡������\n" NOR;
        message_vision(msg,me,target);
        msg = YEL"\n��"HIB"��˼"HIR"��ɱ"HIC"ʽ"NOR+YEL"������\n" NOR;
        msg += CYN"\n������ɽ������ӯ�䣬��Ŀ���\n" NOR;
        msg += CYN"���������۾��ˣ���һʽ�Գ�˼�⾳�����������е�Ǳ�ܣ��������Ҿ�ɱ��\n" NOR;
        message_vision(msg,me,target);
        damage = extra*2 + me->query_skill("force") + me->query_str();
	damage = damage - target->query_temp("apply/armor");
	if( damage < me->query_skill("sword") ) damage = me->query_skill("sword");
        if( random(ap+dp) > dp/2 )
        {
        	damage = damage + random(damage/4);
        	msg = RED"\n$n��$N�޾���˼��Ⱦ������Թ�����ˣ���Ȼ�����˶��$N�����Ҿ�ɱ��\n" NOR;
        	target->receive_damage("kee",damage,me);
	        target->receive_wound("kee",damage/2,me);
	        me->add("force",-damage/5);
	        message_vision(msg, me, target);
	        COMBAT_D->report_status(target);
        }
        else
        {
        	me->add("force",-100);
        	COMBAT_D->do_attack(me, target, weapon);
        }
        if( me->query("jingtian_known") > 1 )
        {
        	msg = YEL"\n��"HIB"���"HIR"��ŭ"HIC"ʽ"NOR+YEL"������\n" NOR;
        	msg += WHT"\n�𷽲���������ǧ�����б��Թ����Թ��ӯ��\n" NOR;
        	msg += WHT"���ŭʽ�����ʱӯ����Թ��ת��ɱ�����ٽ�ɱ��һ��й����ȡ��������\n" NOR;
        	message_vision(msg,me,target);
        	if( random(ap+dp) > dp/2 )
	        {
	        	damage = damage + random(damage/3);
	        	msg = RED"\n$n��$Nӯ����Թ����Ⱦ�����о�����������������$Nһ�����ģ�\n" NOR;
	        	target->receive_damage("kee",damage,me);
		        target->receive_wound("kee",damage/2,me);
		        me->add("force",-damage/5);
		        message_vision(msg, me, target);
		        COMBAT_D->report_status(target);
	        }
	        else
	        {
	        	me->add("force",-100);
	        	COMBAT_D->do_attack(me, target, weapon);
	        }
        }
        if( me->query("jingtian_known") > 2 )
        {
        	msg = YEL"\n��"HIB"�ϳ�"HIR"����"HIC"ʽ"NOR+YEL"������\n" NOR;
        	msg += HIM"\n����ǳЦ����գ��ϳ�����֪Ϊ˭��\n" NOR;
        	msg += HIM"��������ĳ�˼�����������ı��룬���ڻ�������ϳ������һ����\n" NOR;
        	msg += HIM"��ôɽ�˺��ģ���ô������ģ����ǵֲ�סһ�������������ҹ�λء�\n" NOR;
        	msg += HIY"\n\t\t���������ڣ������˶ϳ���\n" NOR;
        	message_vision(msg,me,target);
        	if( random(ap+dp) > dp/2 )
	        {
	        	damage = damage + random(damage/2);
	        	msg = RED"\n$n��$N�ĳ��Ķϳ���Ⱦ���������ң�������Ȥ����ֱ��$N�Ľ���ײ����\n" NOR;
	        	target->receive_damage("kee",damage,me);
		        target->receive_wound("kee",damage/2,me);
		        me->add("force",-damage/5);
		        message_vision(msg, me, target);
		        COMBAT_D->report_status(target);
	        }
	        else
	        {
	        	me->add("force",-100);
	        	COMBAT_D->do_attack(me, target, weapon);
	        }
        }
        me->start_busy(2);
        return 1;
 }
