//bawang-qiang, perform meihua
// /daemon/class/fighter/bawang-qiang/meihua
//梅花六出 要求霸王枪法70级，110级以后出6招
//writted by jie 2001-2-10
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int myskill,times, damage;
        string number,str;
        int cd = 6;
        myskill = (int)me->query_skill("bawang-qiang", 1);  
        weapon = me->query_temp("weapon");
      
        if( !target ) target = offensive_target(me);
        
       
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「梅花六出」？\n");

        if(!me->is_fighting(target))
                return notify_fail("「梅花六出」只能在战斗中使用！\n");
                
        if(!wizardp(me) && me->query("family/family_name") != "将军府" )
                return notify_fail("你是哪儿偷学来的武功，也想用「梅花六出」?\n");
        
        if( me->query("lunhui_zhuanshi") > 3 )
		cd = 5;
	if( time()-(int)me->query_temp("meihua_end") < cd )
                   return notify_fail("你现在真气不纯。\n");
//	if( me->query("pfm_meihua_on") != 1 )
//		return notify_fail("你还不会「梅花六出」。\n");                
                
        //if (me->query_temp("bawang"))
        //   return notify_fail("你正在施用霸字诀，没有余力出「梅花六出」！\n");
        
        if(!objectp(weapon = me->query_temp("weapon"))
           ||(string)weapon->query("skill_type")!="spear")
                return notify_fail("「梅花六出」要用枪才能发挥威力。\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");

	if((int)me->query("force") < 1200 )
		return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < (int)(me->query("max_sen")/2) )
                return notify_fail("你的精神不足，没法子施展梅花六出！\n");

        if(myskill < 100)
                return notify_fail("你的霸王枪法级别还不够。\n");
        else 
            if(myskill <120){
                times = 3;        
                number = "三";}
            else
                if (myskill <160){
                    times = 4;
                    number = "四";}
                else
                    if(myskill <200 ){
                           times = 5;
                           number = "五";}
                     else{ 
                           times = 6;
                           number = "六";}
	me->set_temp("meihua_end",time());
        me->delete("env/brief_message");
	target->delete("env/brief_message");
	damage = me->query_str() + me->query_skill("spear");
	damage = damage + random(damage/3);
        target->add_temp("apply/parry",-damage/2);  
          target->add_temp("apply/dodge",-damage/2);
	message_vision(HIC"\n$N一声长啸，"+ weapon->query("name")+ HIC"光一转，闪电般连续向$n攻出了"+number+"枪，枪枪要命！\n"NOR,me,target);
	me->add("force", -(times*40+60));
        for(int i=1;i<=times;i++)
        COMBAT_D->do_attack(me, target, weapon);
        //COMBAT_D->report_status(target, 0);
        me->receive_damage("sen", times*20);
	target->add_temp("apply/parry",damage/2);  
          target->add_temp("apply/dodge",damage/2);
	if( me->is_fighting(target) && environment(me) == environment(target) && times>5 ) //target->is_fighting()
	{
                target->receive_damage("kee",damage,me);
                target->receive_wound("kee", random(damage)/3, me);
                  			
		message_vision(HIR"\n$n只觉得眼前一花，胸口已被$N的"+ weapon->query("name")+ HIR"搠出一朵灿烂的六出梅花！！！\n\n六个窟窿鲜血喷涌而出．．$n已经气息奄奄．．\n" NOR,me,target);
		COMBAT_D->report_status(target, 0);
		str=me->name()+"使出将军府绝学「"HIR"梅花六出"HIM"」，"+target->name()+NOR+HIM"带着一朵血色灿烂的梅花下了黄泉！";
		if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
    { 
        	message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
    }
	}
        me->start_busy(1+random(2));
        return 1;
}

