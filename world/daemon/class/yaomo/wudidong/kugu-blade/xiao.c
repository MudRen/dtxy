//刀剑笑
//lestat for 枯骨刀 perform
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
      object weapon=me->query_temp("weapon");
      int enhance,damage;
      string msg,str;
      int xcd = 5;
      int djcd = 10;
      if (!weapon) return 0;
      if( !target ) target = offensive_target(me);
      if( !target || !target->is_character()||target->is_corpse()||target==me)
          return notify_fail("你要攻击谁？\n");
      if( !wizardp(me) && me->query("family/family_name")!="陷空山无底洞" )
          return notify_fail("“刀剑笑”只有无底洞门人才可以用！\n");
      if ( !wizardp(me) 
      		&& (me->query_skill("moonforce",1)     
		|| me->query_skill("ningxie-force",1)
		|| me->query_skill("lengquan-force",1)
		|| me->query_skill("zixia-shengong",1)
		|| me->query_skill("zhenyuan-force",1)
		|| me->query_skill("tonsillit",1)
		|| me->query_skill("dragonforce",1)
		|| me->query_skill("huomoforce",1)
		|| me->query_skill("wuxiangforce",1)
		|| me->query_skill("lotusforce",1)
		|| me->query_skill("xuanzong-force",1)
		|| me->query_skill("butian-force",1)
		|| me->query_skill("jiuyin-xinjing",1)) )
          return notify_fail("你不先散了别派内功，怎能学刀剑笑？！\n");
      if( me->query("lunhui_zhuanshi") > 4 )
          xcd = 6;
      if( time()-(int)me->query_temp("xiao_end") < xcd )
          return notify_fail("绝招用多就不灵了！\n");
      if (!target->is_fighting(me))
          return notify_fail("你们没有在打架！\n");
      //if (target->is_busy())
      //    return notify_fail("对方早就手忙脚乱了，放胆攻击吧！\n");
      if (me->query_skill("huntian-qigong",1)<100)
          return notify_fail("你的内功太差，还不会以剑法御刀。\n");
      if (me->query_skill("kugu-blade",1)<100) 
          return notify_fail("你还是先把精力集中在枯骨刀法上吧。\n");
      if (me->query_skill("yinfeng-zhua",1)<100) 
          return notify_fail("你的阴风爪太差，强运神功不是笑死人了。\n");
      if (me->query_skill("qixiu-jian",1)<100)
         return notify_fail("你的七修剑法那么烂，还好意思夹在刀法中现眼？\n");
      if (me->query_skill_mapped("force")!="huntian-qigong")
            return notify_fail("刀剑笑必须配合混天气功才能使用。\n");
      if (me->query_skill_mapped("unarmed")!="yinfeng-zhua")
            return notify_fail("刀剑笑必须配合阴风爪才能发挥威力。\n");
      if (me->query_skill_mapped("sword")!="qixiu-jian")
            return notify_fail("刀剑笑必须配合七修剑才能发挥威力。\n");
      if (me->query("force")<800)
           return notify_fail("你内力不继，难以出招。\n");

    me->add("force", -100);
    seteuid(getuid());
////出剑
    me->set("actions", (: call_other, SKILL_D("qixiu-jian"), "query_action" :) );   
    message_vision(HIB"$N默运混天气功，突然间使出七修剑法，手中"+weapon->name()+HIB"直取$n！\n"NOR,me,target);
    weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","sword");
    enhance=me->query_skill("qixiu-jian",1);
    me->add_temp("apply/attack", enhance);  
    damage=me->query_skill("kugu-blade",1);
    damage=(damage+random(damage))/5;
    me->add_temp("apply/damage",damage);        
    COMBAT_D->do_attack(me, target, weapon);
    weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    me->add_temp("apply/attack",-enhance);
    me->add_temp("apply/damage",-damage);
    me->reset_action();
////出掌
    me->set("actions", (: call_other, SKILL_D("yinfeng-zhua"), "query_action" :) );   
    message_vision(HIC"\n$N不等招式用老，诡异一笑，立刻收刀出爪，一股阴风直扑$n！\n"NOR,me,target);
    //weapon->unequip();
    weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","unarmed");
    enhance=me->query_skill("yinfeng-zhua",1);
    me->add_temp("apply/attack", enhance);  
    damage=me->query_skill("huntian-qigong",1);
    damage=damage/2;
    me->add_temp("apply/damage",damage);        
    COMBAT_D->do_attack(me, target);
    weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    me->add_temp("apply/attack",-enhance);
    me->add_temp("apply/damage",-damage);
    //weapon->wield();
    if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
                       {str=target->name()+HIM"被"+me->name()+"用陷空山绝学"NOR+HIC"「刀剑笑」"+HIM"打死了，据说"+target->name()+"到死脸上还挂着微笑！";
	                 message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	               }
    me->reset_action();
    if( me->query("lunhui_zhuanshi") )
	djcd -= me->query("lunhui_zhuanshi");
    if( me->query("daojian_known") && time()-(int)me->query_temp("daojian_end") > djcd ) //10s 出一次，特殊攻击
    {
    	me->set_temp("daojian_end",time());
    	message_vision(RED"\n$N脸上突然掠过一抹暗红，"+weapon->name()+RED"上泛起血影重重！\n" NOR, me);
    	call_out("blade_attack",1,me,target);
    }
    me->set_temp("xiao_end",time());
//    me->start_busy(random(2)+1);
    return 1;
}

void blade_attack(object me, object target)
{
	int enhance, damage;
	object weapon;
	string str;
	if( !me ) return ;
	if( !target ) target = offensive_target(me);
      	if( !target || !target->is_character()||target->is_corpse()||target==me ) return ;
      	if( !target->is_fighting(me) ) return ;
      	if( (int)me->query("force", 1) < 1000 )
        {
        	message_vision(HIB"$N真气不足，无力出招！\n"NOR,me);
        	return ;
        }
      	weapon = me->query_temp("weapon");
      	enhance = me->query_skill("huntian-qigong",1);
    	damage = me->query_skill("kugu-blade",1);
    	damage = damage + me->query_str();
    	if( weapon )
    		message_vision(RED"\n突然之间，$N将"+weapon->name()+RED"斜斜劈出，带起一片血影腥风逼向$n！\n" NOR, me,target);
    	else
    		message_vision(RED"\n突然之间，$N掌心变得暗红，带起一片血影腥风逼向$n！\n" NOR, me,target);
    	if( random(enhance) > random(target->query_skill("force",1) /4) &&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) )
        {
        	me->add("force",-damage/3);
        	damage = damage + random(damage/2);
        	target->receive_damage("kee",damage,me);
        	target->receive_wound("kee",damage,me);
        	message_vision(HIR"\n这变化过于突然，$n闪避不及，被销魂蚀骨的血雾团团围住。\n" NOR, me,target);
        	message_vision(HIR"$n惨叫一声，从血雾中冲突而出，$N定睛一看，$n早已变得面目全非！\n" NOR, me,target);
        	if( me->query("daojian_known") > 1 ) me->set_temp("hit",1);
        	COMBAT_D->report_status(target,1);
        	message_vision(RED"\n血雾得了$n的精气，血色更盛！\n" NOR, me,target);
        	if( me->query("lunhui_zhuanshi") > 1 )
        		call_out("sword_attack",1,me,target);
        	else
        		call_out("sword_attack",2,me,target);
        }
        else
        {
        	me->add("force",-60);
        	message_vision(HIB"$n见机得早，侧身避过了血雾。\n" NOR, me,target);
        	call_out("sword_attack",1,me,target);
        }
        message_vision(RED"\n那团血雾似有灵性，片刻后飞向$N，缓缓融入了$N体内！\n" NOR, me);
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
        	str=target->name()+HIM"被"+me->name()+"抓碎天灵，饮恨而亡！";
	        message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
	return ;
}

void sword_attack(object me, object target)
{
	int enhance, damage;
	object weapon;
	string str;
	if( !me ) return ;
	if( !target ) target = offensive_target(me);
      	if( !target || !target->is_character()||target->is_corpse()||target==me ) return ;
      	if( !target->is_fighting(me) ) return ;
      	if( (int)me->query("force", 1) < 1000 )
        {
        	message_vision(HIB"$N真气不足，无力出招！\n"NOR,me);
        	return ;
        }
      	weapon = me->query_temp("weapon");
      	enhance = me->query_skill("huntian-qigong",1);
    	damage = me->query_skill("qixiu-jian",1);
    	damage = damage + me->query_str();
    	if( me->query_temp("hit") )
    		damage = damage + me->query_skill("kugu-blade",1);
    	if( weapon )
    		message_vision(RED"\n紧接着，$N招式一变，"+weapon->name()+RED"上泛起剑气千重，重重剑气尽是鲜血般颜色！\n" NOR, me,target);
    	else
    		message_vision(RED"\n紧接着，$N屈指弹出一道血色剑气，直击$n！\n" NOR, me,target);
    	if( random(enhance) > random(target->query_skill("force",1) /3) &&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) )
        {
        	me->add("force",-damage/3);
        	damage = damage + random(damage/2);
        	target->receive_damage("kee",damage,me);
        	target->receive_wound("kee",damage,me);
        	message_vision(HIR"\n结果只听见$n一声惨嚎，剑气已从$n的身上对穿而出，带起漫天血雨！\n" NOR, me,target);
        	if( me->query("daojian_known") > 2 ) me->add_temp("hit",1);
        	COMBAT_D->report_status(target,1);
        	if( me->query("lunhui_zhuanshi") > 3 )
        		call_out("unarmed_attack",1,me,target);
        	else if( me->query("lunhui_zhuanshi") > 2 )
        		call_out("unarmed_attack",2,me,target);
        	else
        		call_out("unarmed_attack",3,me,target);
        	message_vision(RED"\n剑气沾染了$n的鲜血，血色更浓！\n" NOR, me,target);
        }
        else
        {
        	me->add("force",-80);
        	message_vision(HIB"$n顺势一转，轻轻带过，竟然躲过这血色剑气。\n" NOR, me,target);
        	if( me->query("lunhui_zhuanshi") > 2 )
        		call_out("unarmed_attack",1,me,target);
        	else
        		call_out("unarmed_attack",2,me,target);
        }
        message_vision(RED"\n血色剑气绕了个回转，从$N顶门灌顶而入！\n" NOR, me);
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
        	str=target->name()+HIM"被"+me->name()+"抓碎天灵，饮恨而亡！";
	        message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
	return ;
}

void unarmed_attack(object me, object target)
{
	int enhance, damage;
	object weapon;
	string str;
	if( !me ) return ;
	if( !target ) target = offensive_target(me);
      	if( !target || !target->is_character()||target->is_corpse()||target==me ) return ;
      	if( !target->is_fighting(me) ) return ;
      	if( (int)me->query("force", 1) < 1000 )
        {
        	message_vision(HIB"$N真气不足，无力出招！\n"NOR,me);
        	return ;
        }
      	weapon = me->query_temp("weapon");
      	enhance = me->query_skill("huntian-qigong",1);
    	damage = me->query_skill("yinfeng-zhua",1);
    	if( me->query_temp("hit") == 2 )
    		damage = damage + me->query_skill("kugu-blade",1) + me->query_skill("qixiu-jian",1);
    	if( me->query_temp("hit") == 1 )
    		damage = damage + me->query_skill("kugu-blade",1);
    	damage = damage + me->query_str();
    	if( weapon )
    		message_vision(RED"\n$N双目尽赤，"+weapon->name()+RED"上的重重血影缓缓凝成一个巨大的"+BLINK+HIR"血爪"+NOR+RED"，向$n顶盖抓去！\n" NOR, me,target);
    	else
    		message_vision(RED"\n$N双目尽赤，右爪彷若要滴出血来，$N一声嚎叫，右爪带起一片血影，奋力向$n顶盖抓下！\n" NOR, me,target);
    	if( random(enhance) > random(target->query_skill("force",1) /3) &&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) )
        {
        	me->add("force",-damage/3);
        	damage = damage + random(damage/2);
        	target->receive_damage("kee",damage,me);
        	target->receive_wound("kee",damage,me);
        	message_vision(HIR"\n只听见一阵「喀嚓」声响，$n的天灵已经被$N抓碎！\n" NOR, me,target);
        	COMBAT_D->report_status(target,1);
        }
        else
        {
        	me->add("force",-100);
        	message_vision(HIB"可是$n伏地一滚，躲过了$N的最后一击！！\n" NOR, me,target);
        }
        me->delete_temp("hit");
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
        	str=target->name()+HIM"被"+me->name()+"抓碎天灵，饮恨而亡！";
	        message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
	return ;
}