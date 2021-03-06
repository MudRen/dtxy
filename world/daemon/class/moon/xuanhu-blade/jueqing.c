#include <ansi.h>
inherit SSERVER;
int get_current_day_phase();
nosave mapping *day_phase = NATURE_D->query_day_phase();
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
                return notify_fail("你要对谁施展绝情？\n");
        if(!wizardp(me) && me->query("family/family_name") != "月宫")
                return notify_fail(HIG"「绝情」"+NOR"是月宫不传之密！\n");
        if(!me->is_fighting(target))
                return notify_fail("「绝情」只能在战斗中使用！\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不够！\n");
        if ( !me->query("jueqing_known") ) //暂时分为2个阶段 1,2
           return notify_fail("你没有学到的口诀，怎么能领悟到「绝情」的奥秘！\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("你的气血不足，没法子施用外功！\n");

	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("jueqing_end") < cd )
          return notify_fail("你现在内息紊乱，无法使用「绝情」！\n");
        if(me->query_skill("blade", 1) < 200 || me->query_skill("xuanhu-blade", 1) < 200)
                return notify_fail("你的刀法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("whip", 1) < 200 || me->query_skill("jueqingbian", 1) < 200)
                return notify_fail("你的绝情鞭级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("baihua-zhang", 1) < 200)
                return notify_fail("你的掌法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("sword", 1) < 200 || me->query_skill("snowsword", 1) < 200)
                return notify_fail("你的剑法级别还不够，使用这一招会有困难！\n");
        if (me->query_skill_mapped("unarmed")!="baihua-zhang")
                return notify_fail("「绝情」必须配合百花掌才能使用。\n");
        if (me->query_skill_mapped("sword")!="snowsword")
                return notify_fail("「绝情」必须配合风回雪舞剑才能使用。\n");
        if (me->query_skill_mapped("whip")!="jueqingbian")
                return notify_fail("「绝情」必须配合绝情鞭才能使用。\n");

    	weapon=me->query_temp("weapon");
    	message_vision(HIC"\n$N忆起月宫莲湖，手中刀势一缓，合着刀声唱道：\n"NOR,me,target);
    	message_vision(HIC"采莲人语隔秋烟，波静如横练。入手风光莫流转，共留连，画船一笑春风面。\n"NOR,me,target);
	message_vision(HIC"江山信美，终非吾土，问何日是归年？\n"NOR,me,target);
	message_vision(HIW"\n只见$N：纤足踏乾坤，素手拂宝刀。秀目中满是恨断情绝！\n"NOR,me,target);
	enhance=me->query_skill("moonforce",1);
    	damage=me->query_skill("moonshentong",1);
	if( me->query("jueqing_known") == 1 )
	{
		if( target->query_temp("in_qingwang") || target->query_temp("no_move") )
		{
			message_vision(WHT"\n$n与$N目光相对，心头一寒，头脑清醒了许多。\n"NOR,me,target);
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
    	if( phase < 0 || phase > 5 )//晚上
    	{
    		message_vision(HIC"\n$N突然将刀身一横，明晃晃的刀身正对着银盘般的明月！\n"NOR,me);
    		message_vision(HIC"$N娇喝道：嫦娥姐姐借我月华之力，克敌制胜！\n"NOR,me);
    		message_vision(HIC"刹那间：月华大盛，映在刀身上生出皎洁的刀气！\n"NOR,me);
    		message_vision(HIC"\n$N挥刀凌空飞斩$n！\n"NOR,me,target);
    		if( random( me->query("combat_exp")+target->query("combat_exp") ) > target->query("combat_exp") / 3 )
    		{
    			message_vision(HIR"\n结果$n躲闪不及，被刀气横斩而过！\n"NOR,me,target);
    			damage1 = damage + enhance;
			damage1 = damage1 + random(damage1/3);
			target->receive_damage("kee",damage1,me);
			target->receive_wound("kee",damage1,me);
			COMBAT_D->report_status(target,0);
			me->add("force",-damage/5);
	        	if( me->query("force") < 0 ) me->set("force",0);
	        	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )
		        {
				str=me->name()+HIM"使出"+HIC"「月华斩」"+HIM+"将"+target->name()+HIM"生生斩作两片！";
				message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
			}
    		}
    		else
    			message_vision(YEL"\n$n蹬地后跃，原地处被刀气斩出一道丈长的深沟！\n"NOR,me,target);
    	}
    	if( me->query("jueqing_known") > 1 )
	{
		//绝情第二段，可以引天雷降世
		tell_object(me,HIY"\n忽然你觉到一股奇寒真气在你丹田内飞快的转了数周，阴极而阳生，又一股炽热真气从丹田内涌出。\n"NOR,me);
		tell_object(me,HIY"\n两股真气在你丹田内争斗融合，你大惊之后，有会于心，将本派武学融会施展了出来。\n"NOR,me);
		message_vision(WHT"\n$n只见$N神情瞬息万变，最后眼神变得如水般温柔，但身形却陡然间加快。\n"NOR,me,target);
		for(i = 1;i <= 4;i++)
		{
			switch (random(4))
        		{
                        	case 1:
                        	{
                        		//message_vision(HIG"\n四周的风越来越大了。\n"NOR,me);
                        		seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("jueqingbian"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","whip");
					COMBAT_D->do_attack(me, target,weapon);
                                	break;
                        	}
	                        case 2:
	                        {
	                        	//message_vision(HIB"\n天空中云层越来越厚了。\n"NOR,me);
	                        	seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("xuanhu-blade"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","blade");
					COMBAT_D->do_attack(me, target,weapon);
	                                break;
	                        }
	                        case 3:
	                        {
	                        	//message_vision(BLU"\n似乎有几声闷雷响过。\n"NOR,me);
	                        	seteuid(getuid());
					me->set("actions", (: call_other, SKILL_D("baihua-zhang"), "query_action" :) );
					weapon->set("use_apply_skill",1);
					weapon->set("apply/skill_type","unarmed");
					COMBAT_D->do_attack(me, target,weapon);
	                                break;
	                        }
	                        case 0:
	                        {
	                        	//message_vision(CYN"\n天幕被闪电划破几道细痕。\n"NOR,me);
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
		if( (phase >= 0 && phase < 6) && me->query("accept/sun") )//白天
	    	{
	    		message_vision(HIR"\n$N突然停下进攻，望空高喊：太阳神大哥，借你神力，助小妹克敌制胜！\n"NOR,me);
	    		message_vision(HIR"空中闪过一抹赤色光华。$n正觉得$N这举动幼稚可笑，空中一个巨大的火球呼啸着砸向$n！\n"NOR,me,target);
	    		if( random( me->query("combat_exp")+target->query("combat_exp") ) > target->query("combat_exp") / 3 )
	    		{
	    			message_vision(HIR"\n结果$n躲闪不及，被火球当顶砸中！\n"NOR,me,target);
	    			damage1 = damage + enhance;
				damage1 = damage1 + random(damage1/3);
				target->receive_damage("kee",damage1,me);
				target->receive_wound("kee",damage1,me);
				COMBAT_D->report_status(target,0);
				me->add("force",-damage/5);
		        	if( me->query("force") < 0 ) me->set("force",0);
		        	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )
			        {
					str=me->name()+HIM"使出"+HIR"「太阳神之怒」"+HIM+"，巨大的火球从天而降，将"+target->name()+HIM"生生砸死！";
					message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
				}
	    		}
	    		else
	    			message_vision(RED"\n$n蹬地后跃，原地处被火球砸出一个焦黑巨大的深坑！\n"NOR,me,target);
	    	}
		me->add("force", -200);
		tell_object(me,HIY"\n你感到两股真气的争斗已经到了最后关头，丹田内真气鼓荡，仿佛要爆裂开来。\n"NOR,me);
		//               后天福缘                        后天容貌                         后天定力                         后天胆识
		if( !random(10) && random(me->query_kar()) > 20 && random(me->query_per()) > 20 && random(me->query_cps()) > 20 && random(me->query_cor()) > 30 && random(me->query_str()) > 20 && random(me->query_con()) > 20 && random(me->query_int()) > 20 && random(me->query_spi()) > 20 )
		{
                        tell_object(me,HIY"\n两股真气忽然间互相交融，龙虎交汇形成一股更为强大的真气冲入你的奇经八脉。\n"NOR,me);
                        tell_object(me,HIY"\n你被那股真气驱迫着张嘴呐喊，这雏凤一般的清鸣，惊破了天幕，突破了一切的禁忌，在天地间震聋发匮。\n"NOR,me);
                        message_vision(HIY"\n$N呐喊着，天地间只剩下这个唯一的声音，$n看着乌云翻滚，墨色的天空，脸色苍白，心神彻底崩溃！\n"NOR,me,target);
                        message_vision(HIY"\n大地也在这呐喊中开始颤栗，苍天开始了它的震怒；电光霹雳，万物震颤，世间所有的生灵都束手无助！\n"NOR,me,target);
                        target->start_busy(6);
                        me->set_temp("no_move",1);
                        me->start_call_out( (: call_other, __FILE__, "tianlei", me, target :), 2);
        	}
        	else
        	{
        		tell_object(me,HIY"\n两股真气似乎无法分出高低，终于慢慢平息，各自融入丹田之内。\n"NOR,me);
        	}
	}
	else
	{
		message_vision(HIC"\n$N施展完绝情四式，眼神更加冰冷。\n"NOR,me);
		tell_object(me,HIW"\n忽然一股奇寒自你丹田升起，慢慢散入奇经八脉，你一时竟动弹不得。\n"NOR,me);
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
      	message_vision(HIM"\n惊雷夹着巨大的紫芒终于从天而降，击落在你的四周！\n\n"NOR,me);
        for( i = 0;i < sizeof(ob);i++ )
        {
	        if( userp(ob[i]) ) continue;
	        if( ob[i] == me ) continue;
	        if( living(ob[i]) || ob[i]->query("disable_type") == " <昏迷不醒>" )
	        {
	   		str=ob[i]->name()+HIM"被"+me->name()+"招来的天雷击的魂飞魄散，粉身碎骨！";
	   		ob[i]->die();
	   	}
	   	else
	   	{
	   		str=ob[i]->name()+HIM"被"+me->name()+"招来的天雷打成了粉末，灰飞烟灭！";
	   		message_vision("\n" + ob[i]->name() + "化作一股轻烟，缓缓飘散。\n\n",me);
	   		destruct(ob[i]);
	   	}
	        message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
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
