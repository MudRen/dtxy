// rulai jienan-zhi perform如来神掌
// lestat 2001

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
      string msg, dodge_skill;                                
      int damage, jiali, attack, defense, p;
      object weapon = me->query_temp("weapon");
      int cd = 7;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target) )
           return notify_fail("「如来神掌」只能在战斗中对对手使用。\n");        
      if(me->query("family/family_name") != "南海普陀山" )
                return notify_fail("你是哪儿偷学来的武功！\n");
      if( (int)me->query_skill("jienan-zhi",1) < 150 )
           return notify_fail("你的劫难指不够娴熟，不会使用佛门神功「如来神掌」！\n");
      
      if( (int)me->query_skill("unarmed",1) < 150 )
           return notify_fail("你的基本手法不够娴熟，不会使用佛门神功「如来神掌」！\n");

      if( (int)me->query_skill("lotusforce",1) < 150 )
           return notify_fail("你的莲台心法等级不够，不能使用「如来神掌」！\n");  
      
      if( (int)me->query_str() < 24 )
           return notify_fail("你的先天臂力不够强，不能使用「如来神掌」！\n");
      
      if( (int)me->query("max_force") < 1200 )
           return notify_fail("你的内力太弱，不能使用「如来神掌」！\n");
      
      if( (int)me->query("force") < 1500 )
           return notify_fail("你的内力太少了，无法使用出「如来神掌」！\n");   
       
      //if( (int)target->query_condition("dashouyin"))
      //     return notify_fail("对方早已身中「如来神掌」绝技了！\n");   
                
      //if( objectp(weapon = me->query_temp("weapon")) )
      //     return notify_fail("你必须空手使用「如来神掌」！\n");    
      
      if( me->query("lunhui_zhuanshi") > 4 )
		cd = 5;
      else if( me->query("lunhui_zhuanshi") > 1 )
      		cd = 6;
      if( time()-(int)me->query_temp("rulai_end") < cd )
                return notify_fail("你现在内息不顺！\n");
      me->set_temp("rulai_end",time());
      jiali = me->query("force_factor")+1;
      attack = me->query("combat_exp")/10000;
      defense = target->query("combat_exp")/15000;
      me->add_temp("apply/strength", jiali/5);
      target->add_temp("apply/dodge", -jiali);
      target->add_temp("apply/parry", -jiali); 
      //damage = me->query_skill("jienan-zhi", 1)/20 * jiali;
      //if(damage > 800) damage = 800;
      //message_vision(HIR"\n$N突然面色怪异，低声默念佛门真言，双臂骨节一阵爆响，猛然腾空而起，伸手向$n胸前按去，好一式"HIY"「如来神掌」"BLU"！\n"NOR,me,target);
      //“唵 嘛 呢 叭 咪 吽”，
      message_vision(HIY"\n$N双手合十，低声默念佛门真言，以意领音，音生身动！\n"NOR,me,target);
      message_vision("\n"+BLINK+HIW"唵"+NOR+HIR"\n$N顶轮之上，现出一朵红莲！\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"嘛"+NOR+HIG"\n莲花降至$N眉间轮，转为绿色！\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"呢"+NOR+HIY"\n莲花降至$N喉轮，转为金色！\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"叭"+NOR+HIB"\n莲花降至$N心轮，转为蓝色！\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"咪"+NOR+HIM"\n莲花降至$N脐带，转为紫色！\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"吽"+NOR+HIC"\n莲花降至$N阴轮，转为青色！\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision(HIW"\n莲花缓缓降至$N脚下，并发出耀眼的白光，只见$N随白莲腾空而起向$n胸前按去，好一式"HIY"「如来神掌」"HIW"！\n"NOR,me,target);
//      if( attack > defense ) { 
      if( random( attack + defense ) > defense/2 || !living(target) ) 
      { 
      	 /*if( objectp(armor = target->query_temp("armor/cloth"))
      	    && armor->query("armor_prop/armor") < 600
      	    && damage > 100){
                	message_vision(HIY"只见这斗大的掌印正好印在$N的$n"HIY"上，越变越大，竟将它震得粉碎，裂成一块块掉在地上！\n"NOR, target, armor);
                        armor->unequip();
                        armor->move(environment(target));
                        armor->set("name", "破碎的" + armor->query("name"));    
                        armor->set("value", 0);
                        armor->set("armor_prop/armor", 0);
                        target->reset_action();
                        }
         */
         damage = me->query_skill("unarmed")/2 + random(me->query_skill("force")/4);
         damage = damage * 6 + me->query_str();
         damage = damage - target->query_temp("apply/armor");
         if( damage < me->query_str() ) damage = me->query_str();
      	 message_vision(RED"\n$n只觉得霍的胸口一阵剧痛，已经被$N佛家无上念力拍中了前胸！\n"NOR,me,target);
      	 target->apply_condition("dashouyin", 1+(me->query_str()));
      	 target->receive_damage("kee", damage,  me); 
         target->receive_wound("kee", damage/2, me);
         msg = COMBAT_D->damage_msg(damage, "内伤");
         message_vision(msg, me, target);
         me->add("force", -damage/4);
	 COMBAT_D->report_status(target, 1);
	     }
       else 
       {
      	 dodge_skill = target->query_skill_mapped("dodge");
	       if( !dodge_skill ) dodge_skill = "dodge";
         message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
         me->add("force", -100);
        }
//      me->add("force", -200);
      me->start_busy(1+random(2));
      me->add_temp("apply/strength", -jiali/5);
      target->add_temp("apply/dodge", jiali);
      target->add_temp("apply/parry", jiali);

      return 1;
}

 

