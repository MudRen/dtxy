//��Ůɢ��
// lestat 2001

// fixed overflow issue by emotion, 04/29/2006
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        string msg,str;

        int damage, s_num, chance;
        float ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ����Ůɢ������\n");
		if(me->query("family/family_name") != "�¹�")
                return notify_fail("[��Ůɢ��]���¹�����֮�ܣ�\n");
	if(!me->is_fighting(target))
                return notify_fail("����Ůɢ����ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 25+(int)me->query("force_factor") )
                return notify_fail("�������������\n");
        if((int)me->query("kee") < 500 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("baihua-zhang", 1) <80)
                return notify_fail("��İٻ��Ƽ��𻹲�����\n");
        if( time()-(int)me->query_temp("flower_end") < 4 )
          return notify_fail("�����ö�Ͳ����ˣ�\n");
        me->receive_damage("kee", 100);
        msg = MAG
"\n$N΢΢һЦ��������ն����������컨�꣬һʱ��������\n"+
"$nֻ����������Ӱ��ס�ˣ�һʱ��Ȼ��֪����мܣ�������˵�����ˣ�\n\n" NOR;
   s_num = (int)(random(me->query_skill("unarmed")/10)) + (int)(me->query_skill("force")/10)+ 1;
   ap = 0.0 + me->query_skill("unarmed");
   ap =  ap * ap * ap / 20;
   dp = 0.0 + target->query("combat_exp");
   if (dp < 100000) {
   	chance = 100;
   	       }
   else {
   chance = (int)((ap + dp)*random(1000)/1000 * 100 / dp);
   }
   if( chance > 55 )
   {
        me->add("force", -50-(int)me->query("force_factor"));
        damage = s_num * 15 ;
        damage +=(int)me->query("force_factor")-random((int)target->query("force_factor"));
if ( damage > 800 ) damage=800+s_num*3;
        msg += HIM "��Щ���꿴������������ȴ�缲�����������$n,"+HIW+chinese_number(s_num)+HIM"Ƭ���������Ƕ��$n���\n\n" NOR;
	target->receive_damage("kee", damage*3/2,me);
        target->receive_wound("kee", damage,me);
        me->improve_skill("unarmed", s_num, 1);
     }
     else if ( chance > 33 )
     {
        me->add("force", -50-(int)me->query("force_factor")*2/3);
        damage = s_num * 10 ;
if ( damage > 800 ) damage=800+s_num*2;
        msg += HIC "��Щ���꿴������������ȴ�缲�����������$n,$n����������"+HIW+chinese_number(s_num)+HIM"Ƭ������ˣ���\n\n" NOR;
	target->receive_damage("kee", damage*3/2,me);
        target->receive_wound("kee", damage,me);
        me->improve_skill("unarmed", s_num, 1);
     }
   else
   {
     msg += "˭֪$n��������ʤ������һ�ڣ��ѽ����л�����䣡\n";
     me->add("force", -100);
    }

   message_vision(msg, me, target);
   if( damage > 0 ) COMBAT_D->report_status(target);
   else if( damage < 0 ) COMBAT_D->report_status(me);
       if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )
                       {str=target->name()+HIM"��"+me->name()+"�ù㺮���ش�"NOR+HIC"����Ůɢ����"+HIM"�����ˣ���˵ʬ���Ͼ�ȻǶ���������꣡";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
    me->set_temp("flower_end",time());
    return 1;
}
