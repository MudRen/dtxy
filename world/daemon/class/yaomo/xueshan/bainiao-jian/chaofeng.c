//chaofeng.c yushu 2000.10.25
//change busy target and busy self 1 s
//ready for pfm zheng
#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;

        string msg;
        int ii,req,num_anqi,num_hit,max_hit,hitt,damage,op,opfa,remain;
        string anqi_type,b_unit;
        int ap,dp;
	int delay;
	int wound=0;

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
           return notify_fail("��Ҫ����˭��\n");
        
      weapon = me->query_temp("weapon");
      req=(int)me->query_skill("sword", 1)+(int)me->query_skill("bainiao-jian", 1)+(int)me->query_skill("throwing", 1); 


      if (weapon)  
        {
        if (weapon->query("anqi/allow") != 1) num_anqi=0;
        else num_anqi=weapon->query("anqi/now");
        }
       if(!wizardp(me) && me->query("family/family_name")!="��ѩɽ")
          return notify_fail("[���񳯷�]ֻ��ѩɽ���Ӳſ����ã�\n");

      if (me->query_skill_mapped("force")!="ningxie-force")
                return notify_fail("������ϱ�����Ѫ������ʹ�á�\n");
      if(req < 80)
            return notify_fail("�㽣�д����Ĺ��򻹲������\n");
      if(req < 150 && weapon->query("anqi/now") ==0)
            return notify_fail("�㽣��û�а����ɴ�\n");
       if (me->query("force")<200)
           return notify_fail("���������̣������������롣\n");

  if (me->query_temp("chaofeng_busy")) return notify_fail("���������ʤ�����񳯷��ʹ�Ͳ����ˡ�\n");
        me->add("force", -100);

        if(num_anqi <=0) 
           { anqi_type="����"; damage=me->query("force_factor")+10; }
        else if (req < 150)
           { anqi_type=weapon->query("anqi/type"); damage=me->query_temp("apply/damage");}
        else 
           { anqi_type=weapon->query("anqi/type")+"���Ž���";
             damage=me->query_temp("apply/damage")+me->query("force_factor")+10;}
         
        msg = HIW"ֻ��$N����"+weapon->query("name")+HIW"�������ó����콣â������"
                 +anqi_type+HIW"�������Ͷ�ְ���$n������\n" NOR;

        if (num_anqi > 10 || num_anqi == 0) max_hit=10;
        else max_hit=weapon->query("anqi/now");

        num_hit=random(max_hit/2)+(max_hit/2);

        //if (!target->is_fighting(me)) opfa=40;
        //else opfa=30;
        ap = me->query_skill("throwing",1) * 100;
        dp = target->query_skill("dodge",1)+target->query_skill("parry",1)/2;
        if( dp < 1 ) dp = 1;
	if (!target->is_fighting(me)) opfa = ap/dp;
        else opfa = ap*3/dp/4;
        if( opfa > 100 ) op = 100;
       	else op = opfa;
        /*ap = me->query("combat_exp")/1000;
        dp = target->query("combat_exp")/1000;
	if (dp <= 0) dp = 1;
        if (target->query("combat_exp")  !=0 ) 
               op= ap*opfa/dp;
        else op=50;*/
        hitt=0;	
        for (ii=1;ii<=num_hit;ii++)  
          {if (op > random(100)) hitt++;}


        /*if (weapon->query("anqi/type")=="��ȸ��") b_unit="֧";
        else b_unit="��";
        if (weapon->query("anqi/now") != 0) remain=weapon->query("anqi/now")-num_hit;
        else remain=0;
        weapon->set("anqi/now",remain);
        if (weapon->query("anqi/now") == 0) 
          {weapon->delete("anqi/type");  weapon->set("long",weapon->query("orilong"));}
        else weapon->set("long",weapon->query("orilong")+"�����Ѿ�װ��"
           +chinese_number(weapon->query("anqi/now"))+b_unit+weapon->query("anqi/type")+"��������uninstall��\n"); */

        if (hitt==0)
	  {
           msg += HIW "$n��æ����һת�����������������������컨����һ����\n"NOR;
           message_vision(msg, me, target);
           //me->start_busy(random(2));
/*
           if(!target->is_busy())
               target->start_busy(random(3));
*/
	  }
        else 
          {
	   damage=damage*hitt;
           target->receive_damage("kee",damage,me);
      if (damage>target->query_temp("apply/armor"))  {
       target->receive_wound("kee",damage-target->query_temp("apply/armor"),me);
       wound=1;
  }
           msg += HIW "$n��������������"+chinese_number(hitt)+HIW "������"+anqi_type+"��\n"NOR;
           message_vision(msg, me, target);
       //me->start_busy(random(2));
     COMBAT_D->report_status(target,wound);
           //if(!target->is_busy())
           //target->start_busy(random(4));
           }
        	msg = HIW "$n����$N����������ð����ҷŰ�����������ô��ʰ�㣡\n" NOR;     
        	message_vision(msg, me, target);
        	target->kill_ob(me);
      //me->start_busy(1);
      me->set_temp("chaofeng_busy",1);
      delay = 5;
      if( me->query("lunhui_zhuanshi") > 1 )
      	delay = 4;
      call_out("remove_effect",delay,me);
      return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("chaofeng_busy");
}
