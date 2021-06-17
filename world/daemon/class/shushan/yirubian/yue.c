//冷浸溶溶月,思如鞭法lestat/2001.2.14
// modi by xintai 3/2/2001

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg, tparryskill;
        int mjianb, mjianh, tparryb, tparryh, mneili, tneili, mexp, texp, damage;
        object weapon,tweapon;
        int cd = 6;
        msg = "";
        weapon = me->query_temp("weapon");
        mjianb= (int)me->query_skill("whip",1);
        mjianh= (int)me->query_skill("yirubian",1);
        mneili = (int)me->query_skill("force");
        mexp = (int)me->query("combat_exp")/1000;
        if(!objectp(weapon)||(string)weapon->query("skill_type")!="whip")
        	return notify_fail("不拿鞭子怎使『冷浸溶溶月』？\n");
        if(me->query("family/family_name")!="蜀山派")
                return notify_fail("你和李逍遥一点关系都没有，使不出这招！\n");
        if ( mjianh < 80) return notify_fail("你的思如鞭法还不够火候！\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("『冷浸溶溶月』只能在战斗中使用。\n");
        if ((int)me->query("force")<1500)
                return notify_fail("你的内力不够。\n"); 
        if ((int)me->query("sen")<500)
                return notify_fail("你的精神不足。\n"); 
        if( me->query("lunhui_zhuanshi") > 3 )
		cd = 5;
	if( time()-(int)me->query_temp("yue_end") < cd )
          return notify_fail("『冷浸溶溶月』使用不能过于频繁！\n");                
        tweapon = target->query_temp("weapon");  //  Here might be wrong, need to check.
        tparryb= (int)target->query_skill("parry",1);
        tneili = (int)target->query_skill("force");
        texp = (int)target->query("combat_exp")/1000;
        tparryskill = target->query_skill_mapped("parry");
        tparryh=target->query_skill(tparryskill,1);
        me->receive_damage("sen", 100);
        me->set_temp("yue_end",time());
     message_vision(WHT"\n$N招式一变，手中"+weapon->name()+WHT"斜指向下，双眼漠然，一副与世无争的神态，却使出了蜀山绝学\n\n\t\t◆"+BLINK+HIC"冷浸溶溶月"+NOR+WHT"◆\n\n" NOR,me,target);        
     message_vision(HIB"$N向前迈一步，平无华地挥出一鞭，慢，却噼啪作响。\n"NOR,me);
     message_vision(HIB"这一招『无俗念』拼的是内力。\n\n"NOR,me);
     if( random(mneili) > tneili/3 ) 
        {
             msg = HIC"$n只觉得一股劲气象化作千百枚细针一样，穿体而过！\n"
                                "“哇”的一声，$n喷出一大口鲜血，看来是受了内伤！\n\n"NOR;
     damage = mneili + me->query("force_factor");
     damage = damage + random(damage/3);
     damage = damage - target->query_temp("apply/armor");
     if( damage < mneili*2/3 ) damage = mneili*2/3;
     me->add("force",-damage/5);
     target->receive_damage("kee",damage, me);
     target->receive_wound("kee", damage/3, me);
     message_vision(msg, me, target);
     COMBAT_D->report_status(target);
     }
     else {
           me->add("force",-100);
           msg = CYN"$n忙运功向抗，深厚的内力将$N的漫天鞭影都激散了。\n\n"NOR;
           message_vision(msg, me, target);
        }

     message_vision(HIM"$N由静转动，一动便急如风，脚踏奇门，鞭走奇招，每一鞭从$n意想不到的方位无声无息地挥出！\n" NOR,me,target);
     message_vision(HIM"这一招『永矢勿谖』斗的是鞭法！\n\n" NOR,me,target);
     if( random(mjianb + mjianh) > (tparryb+tparryh)/3 )
     {msg = HIC"$n马上手忙脚乱，不知该如何去招架这静若幽冥、快如风的鞭法！\n"
     "果不然，$N的"+weapon->name()+HIC"招招命中，$n浑身上下被抽得遍体鳞伤！\n\n"NOR;
     damage = mjianb + mjianh;
     damage = damage + random(damage/3);
     damage = damage - target->query_temp("apply/armor");
     if( damage < mjianb*2/3 ) damage = mjianb*2/3;
     me->add("force",-damage/5);
     target->receive_damage("kee", damage, me);
     target->receive_wound("kee", damage/3, me);
     message_vision(msg, me, target);
     COMBAT_D->report_status(target);
     }
     else{
          me->add("force",-100);
          msg = CYN"$n却心静如水，丝毫不显慌乱，见招拆招，瓦解了$N这无声的攻势。\n\n"NOR;
          message_vision(msg, me, target);
        }


          message_vision(HIW"$N突然收住身形，回步而立，收鞭于背后，无招胜有招，无形胜有形。\n"NOR,me);
          message_vision(HIW"这一招『独寐寤言』比的是经验！\n\n"NOR,me);
	  if( random(mexp)>(int)(texp/4) )
	  {msg = HIC"$n果然上当，以为$N露出破绽，大喜之下，急忙上前想抢攻。\n"
 	  "$N微微一笑，待$n靠近，长袖一抖，袖尽鞭出，直探$n的胸口。\n"
	  "$n连鞭影还没看到，就差点儿被穿的透心凉！\n\n"NOR;
	  damage = mjianb + mneili;
     	  damage = damage + random(damage/3);
          damage = damage - target->query_temp("apply/armor");
          if( damage < mjianh ) damage = mjianh;
          me->add("force",-damage/5);
	  target->receive_damage("kee", damage, me);
	  target->receive_wound("kee", damage/3, me);
          message_vision(msg, me, target);
          COMBAT_D->report_status(target);
     }
     else{
          me->add("force",-100);
          msg = HIC"$n看破了这招的虚实，将计就计，假装冲上前，却在$N出招的一瞬间腾空而起，回手竟反攻一招！\n\n"NOR;
          message_vision(msg, me, target);
          COMBAT_D->do_attack(target, me, tweapon);
        }
        
        me->start_busy(2);
           
        return 1;
}

