#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,i,lmt;
        object weapon;
	int cd = 5;
        extra = me->query_skill("huntian-jian",1)/10+me->query_skill("sword",1)/10;
        if ( extra < 20) return notify_fail("��Ļ���һ������������������ȼ���\n");

  if(me->query_skill("xuanzong-force",1) < 100)
    return notify_fail("��������ķ���Ƿ�������ʹ������ [�������]��\n");

        if((string)me->query_skill_mapped("force")!="xuanzong-force")
        return notify_fail("������ʱ�����������������ķ�Ϊ���ӡ�\n");
//   if( me->query_temp("pfmxue") ) 
//  return notify_fail("������ȫ������������ѩ��\n");

if(me->query("max_force") < 1000)
      return notify_fail("����������㡣\n");
if(me->query("force") < 1000)
return notify_fail("����������㡣\n");
       if( !target ) target = offensive_target(me);
       if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������ʣ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
	if( me->query("lunhui_zhuanshi") )
		cd = 4;
	if( time()-(int)me->query_temp("lin_end") < cd ) return notify_fail("�����ö�Ͳ����ˣ�\n");
	me->set_temp("lin_end",time());
        weapon = me->query_temp("weapon");

        msg = HIY  "$N˫�ֳֽ���ƽ����֮����һ�Ų�������"+ weapon->name()+  HIY "Ҳ����������������$n"+HIY"������ "NOR+" \n"
                         
          HIR"--------------"+HIY"����һ�� "+HIC"[�������] "HIY+"ת�۶���"HIR+"-----------------"NOR;

        message_vision(msg,me,target);

        me->add_temp("apply/attack",extra);
        me->add_temp("apply/damage",extra);
        lmt = 9;
        for(i=5;i<=lmt;i++)
        {
        me->set_temp("FMZ_perform",i);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        }
        me->add_temp("apply/attack",-extra);
        me->add_temp("apply/damage",-extra);
        me->add("force",-300);
         me->delete_temp("FMZ_perform");
        me->start_busy(1+random(2));
        return 1;
}
