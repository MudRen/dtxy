/*
������ָ������ָ��Ϊ������ʦ������ʱ�����ڽ���ָ֮�󡣵�������
��ʦ�ڷ�������ʱ�����ͬ�Ų��ͣ��󸰷���ɽ�������ɡ�������ʦ��
������Ҷ�ڷ�����ǰ�������֮�о�һ��м���Զ��˴ӷ����黨΢Ц
������Ľ���ָ��Ȼ����֮�Աǡ�����ָ������֮��Ϊ������Ц������
����֮�⡣

�������᱾�������������̨��
����������һ��δ��ǳ�����
*/
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance,damage1,dp;   
  string msg,str;
  int i;
  int cd = 5;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչЦ���᣿\n");
        if(!wizardp(me) && me->query("family/family_name") != "����ɽ���Ƕ�")
                return notify_fail("�㲻�Ƿ���ɽ���Ƕ����ӣ�\n");
        if(!me->is_fighting(target))
                return notify_fail("��û����ս���У�\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("�������������\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        if(me->query_skill("wuxiangforce", 1) < 120)
                return notify_fail("��������񹦵ȼ�̫���ˣ�\n");
        if(me->query_skill("unarmed", 1) < 120)
                return notify_fail("���ȭ�Ź����У�\n");
        if(me->query_skill("puti-zhi", 1) < 120)
                return notify_fail("�������ָ�ȼ�̫���ˣ�\n");
        if( me->query("lunhui_zhuanshi") )
		cd = 4;
        if( time()-(int)me->query_temp("xpt_end") < cd )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->set_temp("xpt_end",time());
        enhance = me->query_skill("wuxiangforce", 1);
        damage1 = me->query_skill("puti-zhi", 1)/3 + me->query_skill("unarmed", 1)/2;
        dp = target->query_temp("apply/armor_vs_force")/2;
        message_vision(HIC"\n$NͻȻ����������ʳָ��סĴָ��"+HIY"�������黨��"+HIC"״��\n"NOR,me,target);
        if( random(enhance) > target->query_skill("dodge",1)/5 )
        {
        	me->add("force", -damage1/6);
        	message_vision(YEL"\n$n������$N����˼����һ��ԥ��\n"NOR,me,target);
          	message_vision(HIC"\n$N���΢Ц����˫ָ���ᵯ��һ�������ֱָ$n��\n"NOR,me,target);
        	message_vision(HIR"\n$n��һ��񣬱�����̴����ұۣ�\n"NOR,me,target);
        	damage=damage1 + random(damage1-dp);
        	if( damage < damage1 ) damage = damage1;
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/3,me);
		COMBAT_D->report_status(target);
		if( random(enhance) > target->query_skill("dodge",1)/4 )
		{
			me->add("force", -damage1/5);
			message_vision(HIC"\n$n�۵Ĵ��˸����飬��æ������\n"NOR,me,target);
			message_vision(HIC"\n��������������$n��ɫͻ�䣬$Nȴ�������ڣ����޶����ֵļ���\n"NOR,me,target);
			message_vision(HIR"\nȴ��$n��$N˫��Ĵָ�������������������ز���\n"NOR,me,target);
			damage=damage1 + random(damage1*2-dp);
			if( damage < damage1 ) damage = damage1;
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/3,me);
			COMBAT_D->report_status(target);
			if( random(enhance) > target->query_skill("dodge",1)/3 )
			{
				me->add("force", -damage1/4);
				message_vision(HIC"\n$n˫�����أ��۵���ɫ���࣡\n"NOR,me,target);
				message_vision(HIC"\n$N���ֶ������ſںȳ�һ����������ֱ��$nͷ����\n"NOR,me,target);
				message_vision(HIR"\n$nʵ���������ܣ���������������������㾫����ң�\n"NOR,me,target);
				damage=damage1 + random(damage1*3-dp);
				if( damage < damage1 ) damage = damage1;
				target->receive_damage("kee",damage,me);
				target->receive_wound("kee",damage/3,me);
				target->receive_wound("sen",damage/3,me);
				COMBAT_D->report_status(target);	
				COMBAT_D->report_sen_status(target);	
			}
		}
        }
        else
        {
		message_vision(HIY"\n$n�����ꡱЦ�������������ϵ���ʱҲ���黨״����\n"NOR,me,target);
		me->add("force", -100);
	}
	//me->start_busy(1+random(2));
	return 1;
}