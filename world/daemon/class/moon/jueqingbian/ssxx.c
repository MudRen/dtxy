//kugu for moon
//2006 ��������
/*
�����䡢���Ǻ��ֱ����������
���ϵر�˫�ɿͣ��ϳἸ�غ��
����Ȥ�����ࡣ���и��гն�Ů����Ӧ���
��������ƣ�ǧɽĺѩ��ֻӰΪ˭ȥ��

���·����į�������ġ���������ƽ�����л��Щ��ർ���
ɽ��������꣬��Ҳ�ʡ�δ���롢ݺ�����Ӿ������
ǧ����š�Ϊ����ɧ�ˣ����ʹ�����������񴦡�

*/ 
/*
          "ǡ������֪����壵��滨��Ժ��",
		"������ǰ�Ȱ��㣬��ɫ�ֻ��䡣",
		"�����񻨷ɶ�أ����ڹ㺮���ڡ�?,
		"�Ѿ��ʹ�������ƻ�ȴ�������ꡣ?,
		"���Է�ǰƮ�������洺�ҿ���δ�����",
		"����ԣ��޾������β��ɡ�",
		"�������������Ắ�����ˡ�",
		"��Ժ�仨�������ϳ�����Զ��",
		"������Ѱ������ȴ��ǧ����",
		"СԺ�����в��������컧�Ƴ���",
*/
#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill,damage,ap,dp;
        string msg;
        int cd = 6;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ����������?\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd = 5;
	if( time()-(int)me->query_temp("ssxx_end") < cd )
                return notify_fail("�����ö�Ͳ����ˣ�\n");
        
        if(!me->is_fighting(target) )
                return notify_fail("��������ֻ����ս����ʹ��!!\n");

        if((int)me->query("max_force") <1000 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 1500 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") <1000 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("jueqingbian",1) <150)
                return notify_fail("��ľ���޼��𻹲���ʩչ��һ����������!!\n");
        if((int)me->query_skill("moondance",1) <150)
                return notify_fail("�������������ȼ�����!!\n");
        if((int)me->query_skill("moonforce",1)<150)
                return notify_fail("���Բ���ķ��ȼ�̫��!!\n");
        if((int)me->query_skill("moonshentong",1) <150)
                return notify_fail("����¹��ɷ��ȼ�����!!\n");
        if( (string)me->query("gender") !="Ů��")
                return notify_fail("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
        if(me->query("family/family_name") != "�¹�" )
                return notify_fail("�㲻���¹�����,���򲻵��޷��ľ���!!\n");
        me->set_temp("ssxx_end",time());
        skill = me->query_skill("whip",1);
        ap = me->query("combat_exp")/1000;
        dp = target->query("combat_exp")/1500;
        weapon=me->query_temp("weapon");
        msg = HIC"\n��������Ϊ���ֱ����������$N����һ�����,���̲�ס�����ݺᣡ\n" NOR;
    	   message_vision(msg, me, target);
    	   msg = HIC"\n������ˮ���㾧Ө��͸������������������\n" NOR;
    	   message_vision(msg, me, target);
    	   if( random(ap) > dp/2 )
    	           msg = WHT"\n$nֻ�����������������в������𣬻������ֻ����������\n" NOR;
    	   else
    	           msg = WHT"\n$n��ǰһ��ģ�����������ֻ����������\n" NOR;
    	   message_vision(msg, me, target);
    	   msg = HIC"\n��ֻ�������˫�ɣ������죬�쿴������ơ�ǧɽĺѩ��\n" NOR;
    	   msg = msg + HIC"\n$n���ھ�̾�컯���棬��ֻ���ͻȻ������£�\n"NOR;
    	   message_vision(msg, me, target);
    	   if( random( ap + dp ) > dp/2 )
    	   {
    	           damage = me->query_skill("whip") + me->query_skill("force") + me->query_str();
    	           damage = damage + random(damage/3);
	 	      damage = damage - target->query_temp("apply/armor");
	 	      if( damage < skill ) damage =  skill;
    	           msg = HIM"\n$n��������,����ֻ������������\n" NOR;
    	           target->receive_damage("kee",damage,me);
	           target->receive_wound("kee",damage/2,me);
	           message_vision(msg, me, target);
	           COMBAT_D->report_status(target);
	           me->add("force",-damage/6);
	           me->receive_damage("sen",damage/10);
    	   }
    	   else
    	   {
    	           me->add("force",-100);
	           me->receive_damage("sen",100);
    	           message_vision(HIB"\n$n��������ǰ������ʧ�ˣ�����΢���ź���\n" NOR,me,target);
    	   }
        return 1;
}
