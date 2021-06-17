#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i;
  int cd = 10;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�������\n");
        if(!wizardp(me) && me->query("family/family_name") != "����ɢ��")
                return notify_fail(HIG"���������"+NOR"��ɢ�ɲ���֮�ܣ�\n");
        if(!me->is_fighting(target))
                return notify_fail("���������ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("�������������\n");
        if ( !me->query("icefire_known") ) //��ʱ��Ϊ2���׶� 1,2
           return notify_fail("��û��ѧ���Ŀھ�����ô�����򵽡���������İ��أ�\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("icefire_end") < cd )
          return notify_fail("��������Ϣ���ң��޷�ʹ�á����������\n");
        if(me->query_skill("whip", 1) < 200 || me->query_skill("wuwei-fuchen", 1) < 200)
                return notify_fail("��ı޷����𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("ice_fire_zhang", 1) < 200)
                return notify_fail("����Ʒ����𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("force", 1) < 200 || me->query_skill("butian-force", 1) < 200)
                return notify_fail("����ڹ����𻹲�����ʹ����һ�л������ѣ�\n");
        if (me->query_skill_mapped("force")!="butian-force")
                return notify_fail("���������������ϲ����ķ�����ʹ�á�\n");
        if (me->query_skill_mapped("whip")!="wuwei-fuchen")
                return notify_fail("������������������Ϊ��������ʹ�á�\n");
    	weapon=me->query_temp("weapon");
    	me->add("force",-500);
    	enhance = me->query_skill("butian-force",1)/10;
    	me->add_temp("apply/damage",enhance*(2+me->query("icefire_known")));
    	me->add_temp("apply/strength",enhance*(1+me->query("icefire_known")));
	target->add_temp("apply/dodge",-enhance*(2+me->query("icefire_known")));
        target->add_temp("apply/parry",-enhance*(1+me->query("icefire_known")));
    	if( me->query("icefire_known") > 1 )
	{
		message_vision(HIC"\n$Nͬʱ��ת"+HIW"����"+HIR"����"+HIC"�ķ��������Ե���ӿ��˫�ۡ�\n"NOR,me,target);
		message_vision(HIC"���ꡱ��һ��"+BLINK+HIW"���ǵ�"+NOR+HIC"��$N����������ɣ���"+BLINK+HIR"���浶"+NOR+HIC"ͬʱ��$N��������ȼ��\n"NOR,me);
	}
	else
	{
		message_vision(HIW"\n$N��ת�����ķ�����������쳣���䣬�Ե���ӿ����ۡ�\n"NOR,me);
		message_vision(HIC"���ꡱ��һ��"+BLINK+HIW"���ǵ�"+NOR+HIC"��$N����������ɣ�\n"NOR,me);
	}	
	me->set_temp("icefire",1);
	COMBAT_D->do_attack(me, target, weapon);
	if( me->query("icefire_known") == 1 )
	{
		message_vision(HIR"\n$N��ת�����ķ���������ת����˲����������������ӿ���ұۡ�\n"NOR,me);
		message_vision(BLINK+HIR"���浶"+NOR+HIR"��$N��������ȼ��"+HIC"���ꡱ��һ��"+HIW"���ǵ�"+NOR+HIC"����ˮ����ɢ��ȥ��\n"NOR,me);
	}
	me->set_temp("icefire",2);
	COMBAT_D->do_attack(me, target, weapon);
	if( me->query("icefire_known") > 1 )
	{
		me->set_temp("icefire",3);
		COMBAT_D->do_attack(me, target, weapon);
		message_vision(HIR"\n$N��Ȼ������ת�����ķ���\n"NOR,me);
		message_vision(HIC"���ꡱ��һ��"+HIW"���ǵ�"+NOR+HIC"����ˮ������"+HIR"���浶"+NOR+HIC"���������ܣ�"+HIR"���浶"+NOR+HIC"���Ƹ�ʢ��\n"NOR,me);
		message_vision(HIR"���浶"+NOR+HIC"����ɫ��ˮ����Χ���������ѣ�����һ��"+HIW"��"+HIR"��"+HIC"���ޡ�\n"NOR,me);
		weapon = new("/d/sanxian/obj/icefirewhip");
		me->set_temp("weapon",weapon);
	}
	else
	{
		message_vision(HIR"\n$N��Ȼ������ת�����ķ���\n"NOR,me);
		message_vision(HIR"���浶���ƴ�ʢ�������ѣ�����һ���һ𳤱ޡ�\n"NOR,me);
		weapon = new("/d/sanxian/obj/firewhip");
		me->set_temp("weapon",weapon);
	}
	me->reset_action();
	me->add_temp("apply/damage",damage);
	COMBAT_D->do_attack(me, target, weapon);
	COMBAT_D->do_attack(me, target, weapon);
	COMBAT_D->do_attack(me, target, weapon);
	me->delete_temp("weapon");
	destruct(weapon);
	if( me->query("icefire_known") > 1 )
	{
		message_vision(HIC"\n$N����"+HIR"�����ķ�"+HIC"��ת����"+HIW"�����ķ�"+HIC"���٣�����תΪ������\n"NOR,me);
		message_vision(HIR"���浶"+WHT"����ˮ����������"+HIW"���ǵ�"+WHT"����"+HIR"���浶"+WHT"Χ�����롣\n"NOR,me);
		message_vision(YEL"$n�������Ż����ڱ��еĹ���ʹ��ҡҡ�Դ���$N�û�����$n��\n"NOR,me,target);
		if( random( me->query("combat_exp")+target->query("combat_exp") ) > target->query("combat_exp") /2 )
		{
			message_vision(HIR"\n���$n�������������̸����ţ���Ѫ���ؿ����������\n"NOR,me,target);
			damage = me->query_skill("spysword",1);
			damage = damage + random(damage/3);
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage,me);
			COMBAT_D->report_status(target,0);
	        	me->add("force",-damage/5);
	        	message_vision(YEL"\n$N��"+HIW"���ǵ�"+YEL"����$n���ڣ������ˡ�\n"NOR,me,target);
	        	message_vision(HIW"���ǵ�"+HIR"ʧȥ$N������֧�֣����顱��ը�˿�����$n��ը��Ѫ��ģ�����Ҳ��̶ã�\n"NOR,me,target);
	        	damage = me->query_skill("ice_fire_zhang",1);
	        	damage = damage + random(damage/3);
	        	target->receive_damage("kee",damage,me);
        		target->receive_wound("kee",damage,me);
			COMBAT_D->report_status(target,0);
	        	me->add("force",-damage/5);
	        	if( me->query("force") < 0 ) me->set("force",0);
	        	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
		        {
				str=target->name()+HIM"��"+me->name()+HIM"�á�"+HIW"��"+HIR"��"+HIC"��"+HIM+"��������ը������Ƭ��";
				message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
			}
		}
		else
		{
			message_vision(RED"\n���$n�������ѣ�����Ծ����"+HIW"���ǵ�"+NOR+RED"��$n���ը������$n�ŵ���ɫ�԰ף�\n"NOR,me,target);
		}
	}
	else
	{
		message_vision(RED"\n$N���������ķ���"+HIR"���浶"+NOR+RED"����ƽϢ�ˡ�\n"NOR,me);
	}
        me->add_temp("apply/damage",-enhance*(2+me->query("icefire_known")));
        me->add_temp("apply/strength",-enhance*(1+me->query("icefire_known")));
        target->add_temp("apply/dodge",enhance*(2+me->query("icefire_known")));
        target->add_temp("apply/parry",enhance*(1+me->query("icefire_known")));
	me->delete_temp("icefire");
    	me->reset_action();
	me->start_busy(2);
    	me->set_temp("icefire_end",time());	
  return 1;
}
