#include <ansi.h>
inherit SSERVER;
int get_current_day_phase();
static mapping *day_phase = NATURE_D->query_day_phase(); 
int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i,damage1;
  int phase = get_current_day_phase();
  int cd = 10;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ���飿\n");
        if(!wizardp(me) && me->query("family/family_name") != "�¹�")
                return notify_fail(HIG"�����项"+NOR"���¹�����֮�ܣ�\n");
        if(!me->is_fighting(target))
                return notify_fail("�����项ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("�������������\n");
        if ( !me->query("jueqing_known") ) //��ʱ��Ϊ2���׶� 1,2
           return notify_fail("��û��ѧ���Ŀھ�����ô�����򵽡����项�İ��أ�\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("jueqing_end") < cd )
          return notify_fail("��������Ϣ���ң��޷�ʹ�á����项��\n");
        if(me->query_skill("blade", 1) < 200 || me->query_skill("xuanhu-blade", 1) < 200)
                return notify_fail("��ĵ������𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("whip", 1) < 200 || me->query_skill("jueqingbian", 1) < 200)
                return notify_fail("��ľ���޼��𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("baihua-zhang", 1) < 200)
                return notify_fail("����Ʒ����𻹲�����ʹ����һ�л������ѣ�\n");
        if(me->query_skill("sword", 1) < 200 || me->query_skill("snowsword", 1) < 200)
                return notify_fail("��Ľ������𻹲�����ʹ����һ�л������ѣ�\n");
        if (me->query_skill_mapped("unarmed")!="baihua-zhang")
                return notify_fail("�����项������ϰٻ��Ʋ���ʹ�á�\n");
        if (me->query_skill_mapped("sword")!="snowsword")
                return notify_fail("�����项������Ϸ��ѩ�轣����ʹ�á�\n");
        if (me->query_skill_mapped("whip")!="jueqingbian")
                return notify_fail("�����项������Ͼ���޲���ʹ�á�\n");

    	weapon=me->query_temp("weapon");
    	message_vision(HIC"\n$N�����¹����������е���һ�������ŵ���������\n"NOR,me,target);
    	message_vision(HIC"������������̣���������������ַ��Ī��ת��������������һЦ�����档\n"NOR,me,target);
	message_vision(HIC"��ɽ�������շ��������ʺ����ǹ��ꣿ\n"NOR,me,target);
	message_vision(HIW"\nֻ��$N������̤Ǭ�������ַ���������Ŀ�����Ǻ޶������\n"NOR,me,target);
	enhance=me->query_skill("moonforce",1);
    	damage=me->query_skill("moonshentong",1);
	if( me->query("jueqing_known") == 1 )
	{
		if( target->query_temp("in_qingwang") || target->query_temp("no_move") )
		{
			message_vision(WHT"\n$n��$NĿ����ԣ���ͷһ����ͷ����������ࡣ\n"NOR,me,target);
			target->delete_temp("in_qingwang");
			target->delete_temp("no_move");
		}
	}
	else
		target->start_busy(1);
	  target->add_temp("apply/dodge",-enhance/2);
    target->add_temp("apply/parry",-damage/2);
    me->add_temp("apply/attack",enhance/2);
    me->add_temp("apply/damage",damage/2);
    	COMBAT_D->do_attack(me, target, weapon);
    	COMBAT_D->do_attack(me, target, weapon);
    	COMBAT_D->do_attack(me, target, weapon);
    	COMBAT_D->do_attack(me, target, weapon);
    	if( phase < 0 || phase > 5 )//����
    	{
    		message_vision(HIC"\n$NͻȻ������һ�ᣬ���λεĵ������������̰�����£�\n"NOR,me);
    		message_vision(HIC"$N���ȵ����϶�������»�֮�����˵���ʤ��\n"NOR,me);
    		message_vision(HIC"ɲ�Ǽ䣺�»���ʢ��ӳ�ڵ�����������ĵ�����\n"NOR,me);
    		message_vision(HIC"\n$N�ӵ���շ�ն$n��\n"NOR,me,target);
    		if( random( me->query("combat_exp")+target->query("combat_exp") ) > target->query("combat_exp") / 3 )
    		{
    			message_vision(HIR"\n���$n������������������ն������\n"NOR,me,target);
    			damage1 = damage + enhance;
			damage1 = damage1 + random(damage1/3);
			target->receive_damage("kee",damage1,me);
			target->receive_wound("kee",damage1,me);
			COMBAT_D->report_status(target,0);
			me->add("force",-damage/5);
	        	if( me->query("force") < 0 ) me->set("force",0);
	        	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
		        {
				str=me->name()+HIM"ʹ��"+HIC"���»�ն��"+HIM+"��"+target->name()+HIM"����ն����Ƭ��";
				message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
			}
    		}
    		else
    			message_vision(YEL"\n$n�ŵغ�Ծ��ԭ�ش�������ն��һ���ɳ������\n"NOR,me,target);
    	}
    	if( me->query("jueqing_known") > 1 )
	{
		//����ڶ��Σ����������׽���
		tell_object(me,HIY"\n��Ȼ�����һ���溮�������㵤���ڷɿ��ת�����ܣ���������������һ�ɳ��������ӵ�����ӿ����\n"NOR,me);
		tell_object(me,HIY"\n�����������㵤���������ںϣ����֮���л����ģ���������ѧ�ڻ�ʩչ�˳�����\n"NOR,me);
		message_vision(WHT"\n$nֻ��$N����˲Ϣ��䣬�����������ˮ�����ᣬ������ȴ��Ȼ��ӿ졣\n"NOR,me,target);
		for(i = 1;i <= 4;i++)
		{
			switch (random(4))
        		{
                        	case 1:
                        	{ 
                        		//message_vision(HIG"\n���ܵķ�Խ��Խ���ˡ�\n"NOR,me);
                        		seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("jueqingbian"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","whip");
					COMBAT_D->do_attack(me, target,weapon);
                                	break;
                        	}
	                        case 2: 
	                        {
	                        	//message_vision(HIB"\n������Ʋ�Խ��Խ���ˡ�\n"NOR,me);
	                        	seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("xuanhu-blade"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","blade");
					COMBAT_D->do_attack(me, target,weapon);
	                                break;
	                        } 
	                        case 3: 
	                        {
	                        	//message_vision(BLU"\n�ƺ��м������������\n"NOR,me);
	                        	seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("baihua-zhang"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","unarmed");
					COMBAT_D->do_attack(me, target,weapon);
	                                break;
	                        }
	                        case 0: 
	                        {
	                        	//message_vision(CYN"\n��Ļ�����绮�Ƽ���ϸ�ۡ�\n"NOR,me);
	                        	seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("snowsword"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","sword");
					me->set_temp("WX_perform", 7+random(5));
					COMBAT_D->do_attack(me, target,weapon);
	                                break;
	                        }
                	}   
		}
		if( (phase >= 0 && phase < 6) && me->query("accept/sun") )//����
	    	{
	    		message_vision(HIR"\n$NͻȻͣ�½��������ոߺ���̫�����磬������������С�ÿ˵���ʤ��\n"NOR,me);
	    		message_vision(HIR"��������һĨ��ɫ�⻪��$n������$N��ٶ����ɿ�Ц������һ���޴�Ļ����Х������$n��\n"NOR,me,target);
	    		if( random( me->query("combat_exp")+target->query("combat_exp") ) > target->query("combat_exp") / 3 )
	    		{
	    			message_vision(HIR"\n���$n���������������򵱶����У�\n"NOR,me,target);
	    			damage1 = damage + enhance;
				damage1 = damage1 + random(damage1/3);
				target->receive_damage("kee",damage1,me);
				target->receive_wound("kee",damage1,me);
				COMBAT_D->report_status(target,0);
				me->add("force",-damage/5);
		        	if( me->query("force") < 0 ) me->set("force",0);
		        	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
			        {
					str=me->name()+HIM"ʹ��"+HIR"��̫����֮ŭ��"+HIM+"���޴�Ļ�������������"+target->name()+HIM"����������";
					message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
				}
	    		}
	    		else
	    			message_vision(RED"\n$n�ŵغ�Ծ��ԭ�ش��������ҳ�һ�����ھ޴����ӣ�\n"NOR,me,target);
	    	}
		me->add("force", -200);
		tell_object(me,HIY"\n��е����������������Ѿ���������ͷ�������������ĵ����·�Ҫ���ѿ�����\n"NOR,me);
		//               ���츣Ե                        ������ò                         ���춨��                         ���쵨ʶ
		if( !random(10) && random(me->query_kar()) > 20 && random(me->query_per()) > 20 && random(me->query_cps()) > 20 && random(me->query_cor()) > 30 && random(me->query_str()) > 20 && random(me->query_con()) > 20 && random(me->query_int()) > 20 && random(me->query_spi()) > 20 )
		{
                        tell_object(me,HIY"\n����������Ȼ�以�ཻ�ڣ����������γ�һ�ɸ�Ϊǿ���������������澭������\n"NOR,me);
                        tell_object(me,HIY"\n�㱻�ǹ����������������ź��������һ�����������������Ļ��ͻ����һ�еĽ��ɣ�����ؼ��������ѡ�\n"NOR,me);
                        message_vision(HIY"\n$N�ź��ţ���ؼ�ֻʣ�����Ψһ��������$n�������Ʒ�����īɫ����գ���ɫ�԰ף����񳹵ױ�����\n"NOR,me,target);
                        message_vision(HIY"\n���Ҳ�����ź��п�ʼ���������쿪ʼ��������ŭ���������������������������е����鶼����������\n"NOR,me,target);
                        target->start_busy(6);
                        me->set_temp("no_move",1);
                        me->start_call_out( (: call_other, __FILE__, "tianlei", me, target :), 2);
        	}
        	else
        	{
        		tell_object(me,HIY"\n���������ƺ��޷��ֳ��ߵͣ���������ƽϢ���������뵤��֮�ڡ�\n"NOR,me);
        	}               
	}
	else
	{
		message_vision(HIC"\n$Nʩչ�������ʽ��������ӱ��䡣\n"NOR,me);
		tell_object(me,HIW"\n��Ȼһ���溮���㵤����������ɢ���澭��������һʱ���������á�\n"NOR,me);
	}	
	weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    	weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
	me->delete_temp("WX_perform");
    	me->reset_action();
    	me->add("force", -300);
	me->start_busy(2);
	target->add_temp("apply/dodge",enhance/2);
        target->add_temp("apply/parry",damage/2);
        me->add_temp("apply/attack",-enhance/2);
    	me->add_temp("apply/damage",-damage/2);
    	me->set_temp("jueqing_end",time());	
  return 1;
}
void tianlei(object me, object target)
{
        string msg,str;
        int i;
        object *ob = all_inventory(environment(me));
	if(!me) 
      		return;
      	me->delete_temp("no_move");
      	if( !sizeof(ob) )
      		return;
      	message_vision(HIM"\n���׼��ž޴����â���ڴ��������������������ܣ�\n\n"NOR,me);
        for( i = 0;i < sizeof(ob);i++ )
        {
	        if( userp(ob[i]) ) continue;
	        if( ob[i] == me ) continue;
	        if( living(ob[i]) || ob[i]->query("disable_type") == " <���Բ���>" )
	        {
	   		str=ob[i]->name()+HIM"��"+me->name()+"���������׻��Ļ����ɢ��������ǣ�";
	   		ob[i]->die();
	   	}
	   	else
	   	{
	   		str=ob[i]->name()+HIM"��"+me->name()+"���������״���˷�ĩ���ҷ�����";
	   		message_vision("\n" + ob[i]->name() + "����һ�����̣�����Ʈɢ��\n\n",me);
	   		destruct(ob[i]);
	   	}
	        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
	return ;
}

int get_current_day_phase() 
{
    // ref. /adm/daemons/natured.c:init_day_phase()
    mixed *local = localtime(time()*60);
    int t = local[2] * 60 + local[1];
    int i;
    for (i=0; i<sizeof(day_phase); i++)
        if (t>=day_phase[i]["length"])
            t -= (int)day_phase[i]["length"];
        else
            break;
    return (i==0 ? sizeof(day_phase)-1 : i-1);
}
