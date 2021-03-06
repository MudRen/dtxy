
#include <ansi.h>
#include <combat.h>

inherit SSERVER;

void feijian_ok(object);
void postfeijian(object,object,object,int);

mapping feijian= ([
       "damage": 60,
       "force" : 60,
       "dodge" : -80,
       "parry" : -50,
       "damage_type" : "刺伤",
       "action" :  HIW"$w"+HIW"在空中幻出道道剑光，飞鸟投林般，向$n的$l扑去"NOR,
       "post_action" : (: postfeijian :)
    ]);
mapping feijian1= ([
       "damage": 80,
       "force" : 80,
       "dodge" : -90,
       "parry" : -60,
       "damage_type" : "刺伤",
       "action" :  HIW"$w"+HIW"在空中一个转折，速度陡然加快，闪电般扑向$n的$l"NOR,
       "post_action" : (: postfeijian :)
    ]);

int perform(object me, object target)
{
      object weapon=me->query_temp("weapon");
      if(!wizardp(me) && me->query("family/family_name")!="大雪山")
          return notify_fail("[飞鸟投林]只有雪山弟子才可以用！\n");
      if( !target ) target = offensive_target(me);
      if( !target || !target->is_character()||target->is_corpse()||target==me)
          return notify_fail("你要攻击谁？\n");
      if (!target->is_fighting(me))
             return notify_fail("你们没有在打架！\n");
      if (me->query_temp("no_feijian") )
          return notify_fail("你现在状态不佳，不能使用飞剑。\n");      
      if (me->query_skill("ningxie-force",1)<120)
          return notify_fail("你的内功太差，剑飞出去肯定飞不回来。\n");
      if (me->query_skill("bainiao-jian",1)<120) 
          return notify_fail("你的百鸟剑法那么烂，当心把剑插自己身上。\n");
    if (me->query_skill("throwing",1)<120)
        return notify_fail("你的暗器功夫太差，胡乱把剑扔出去，肯定找不到目标。\n");
      if (me->query("force")<600)
           return notify_fail("你内力不继，难以驾御飞剑。\n");
     me->delete("env/brief_message");
   target->delete("env/brief_message");
      me->add("force", -100);
      me->set("actions",feijian);
    message_vision(HIW"$N突然清啸一声，掌中"+weapon->query("name")+HIW"脱手而出，化做一道长虹，直向$n飞去！"NOR,me,target);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
      me->set_temp("no_feijian",1);
      call_out("feijian_ok",2+random(2),me);
      me->reset_action();
      return 1;
}

void feijian_ok(object me) {
      int count, damage;
      if (!me) return;
      me->delete_temp("no_feijian");
      count = me->query_temp("feijian_count");
      damage = (1 + count) * count * 5;
      me->add_temp("apply/damage", -damage);
      me->delete_temp("feijian_count");
}

void postfeijian(object me,object victim,object weapon, int damage) {
      int count;
      if (damage > 0 || damage == RESULT_DODGE || damage == RESULT_FORCE )
         message_vision(HIW""+weapon->query("name")+HIW"在空中打了个转，又飞回到$N手中。\n"NOR,me);
      else {
      	   me->add_temp("feijian_count", 1);
      	   count = me->query_temp("feijian_count");
           //message_vision(HIW""+weapon->query("name")+HIW"改变方向，“唰”的一声，斜斜插在地上。\n"NOR,me);
           message_vision(HIY""+weapon->query("name")+HIY"弹跃在半空。\n"NOR,me,victim);
           //if( me->is_busy() && !victim->is_busy() ) victim->start_busy(1);
           //me->start_busy(1);
           me->set("actions",feijian1);
           me->add_temp("apply/damage", count * 10);
           COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
           me->reset_action();
           //weapon->move(environment(me));
      }
}
