//���������,˼��޷�lestat/2001.2.14
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
        	return notify_fail("���ñ�����ʹ����������¡���\n");
        if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("�������ңһ���ϵ��û�У�ʹ�������У�\n");
        if ( mjianh < 80) return notify_fail("���˼��޷����������\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����������¡�ֻ����ս����ʹ�á�\n");
        if ((int)me->query("force")<1500)
                return notify_fail("�������������\n"); 
        if ((int)me->query("sen")<500)
                return notify_fail("��ľ����㡣\n"); 
        if( me->query("lunhui_zhuanshi") > 3 )
		cd = 5;
	if( time()-(int)me->query_temp("yue_end") < cd )
          return notify_fail("����������¡�ʹ�ò��ܹ���Ƶ����\n");                
        tweapon = target->query_temp("weapon");  //  Here might be wrong, need to check.
        tparryb= (int)target->query_skill("parry",1);
        tneili = (int)target->query_skill("force");
        texp = (int)target->query("combat_exp")/1000;
        tparryskill = target->query_skill_mapped("parry");
        tparryh=target->query_skill(tparryskill,1);
        me->receive_damage("sen", 100);
        me->set_temp("yue_end",time());
     message_vision(WHT"\n$N��ʽһ�䣬����"+weapon->name()+WHT"бָ���£�˫��ĮȻ��һ��������������̬��ȴʹ������ɽ��ѧ\n\n\t\t��"+BLINK+HIC"���������"+NOR+WHT"��\n\n" NOR,me,target);        
     message_vision(HIB"$N��ǰ��һ����ƽ�޻��ػӳ�һ�ޣ�����ȴ��ž���졣\n"NOR,me);
     message_vision(HIB"��һ�С������ƴ����������\n\n"NOR,me);
     if( random(mneili) > tneili/3 ) 
        {
             msg = HIC"$nֻ����һ�ɾ�������ǧ��öϸ��һ�������������\n"
                                "���ۡ���һ����$n���һ�����Ѫ���������������ˣ�\n\n"NOR;
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
           msg = CYN"$næ�˹��򿹣�����������$N�������Ӱ����ɢ�ˡ�\n\n"NOR;
           message_vision(msg, me, target);
        }

     message_vision(HIM"$N�ɾ�ת����һ���㼱��磬��̤���ţ��������У�ÿһ�޴�$n���벻���ķ�λ������Ϣ�ػӳ���\n" NOR,me,target);
     message_vision(HIM"��һ�С���ʸ���Ρ������Ǳ޷���\n\n" NOR,me,target);
     if( random(mjianb + mjianh) > (tparryb+tparryh)/3 )
     {msg = HIC"$n������æ���ң���֪�����ȥ�м��⾲����ڤ�������ı޷���\n"
     "����Ȼ��$N��"+weapon->name()+HIC"�������У�$n�������±���ñ������ˣ�\n\n"NOR;
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
          msg = CYN"$nȴ�ľ���ˮ��˿�����Ի��ң����в��У��߽���$N�������Ĺ��ơ�\n\n"NOR;
          message_vision(msg, me, target);
        }


          message_vision(HIW"$NͻȻ��ס���Σ��ز��������ձ��ڱ�������ʤ���У�����ʤ���Ρ�\n"NOR,me);
          message_vision(HIW"��һ�С�������ԡ��ȵ��Ǿ��飡\n\n"NOR,me);
	  if( random(mexp)>(int)(texp/4) )
	  {msg = HIC"$n��Ȼ�ϵ�����Ϊ$N¶����������ϲ֮�£���æ��ǰ��������\n"
 	  "$N΢΢һЦ����$n����������һ�����価�޳���ֱ̽$n���ؿڡ�\n"
	  "$n����Ӱ��û�������Ͳ���������͸������\n\n"NOR;
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
          msg = HIC"$n���������е���ʵ�����ƾͼƣ���װ����ǰ��ȴ��$N���е�һ˲���ڿն��𣬻��־�����һ�У�\n\n"NOR;
          message_vision(msg, me, target);
          COMBAT_D->do_attack(target, me, tweapon);
        }
        
        me->start_busy(2);
           
        return 1;
}

