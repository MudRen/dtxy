
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,i,dlkm,temp_extra,extra1;
        object weapon;
        int cd = 5;
       if (!(wizardp(me))) {
       if( !wizardp(me) && (string)me->query("family/family_name") != "����ɢ��" )
                return notify_fail("��Ĵ̿ͽ��������״�������ʹ��[ͼ��ذ��]��\n");
       }
        extra = me->query_skill("spysword",1);
        temp_extra=extra;
if(me->query("force") < 1000||me->query("max_force")<1200) return notify_fail("���״̬���ã��޷�ʹ��[ͼ��ذ��]��\n");
        if ( extra < 120) return notify_fail("��Ĵ̿ͽ������𻹲�����ʹ����һ�л���һ���Ѷȣ�\n");
        if( (int)me->query_skill("sword", 1) < 120)
                return notify_fail("��Ľ�����Ƿȱ�������޷�����Ӧ�֡�\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ͼ��ذ�֣�ֻ����ս����ʹ�á�\n");
       if( me->query("lunhui_zhuanshi") > 1 )
		cd = 4;
       if(time()-me->query_temp("bishou_end")<cd) return notify_fail("�̿ͽ��������õ���ôƵ����\n");         
        me->set_temp("bishou_end",time());
        weapon = me->query_temp("weapon");
        msg = HIW "\n$NͻȻ��������"+ weapon->name()+ HIW"��������Ϣ���ߵ�$n��ߣ�\n" NOR;
        message_vision(msg,me,target);
        me->add_temp("apply/attack",temp_extra/5);
        me->add_temp("apply/damage",temp_extra/5);
        dlkm = extra/50;
        if( dlkm > 4 ) dlkm = 4;
        if( random(dlkm) == 1 ) dlkm += random(2);
        if( me->query("lunhui_zhuanshi") > 4 ) dlkm += random(2);
        extra1 = extra * dlkm / 2;
        for(i=1;i<=dlkm;i++)
        {msg="";
         if(i==1)  msg = HIG "\n�۴̿ͽ�����-- �׺���գ�\n" NOR;
         else if(i==2)  msg = HIR "\n�۴̿ͽ�����-- ��Ѫ�岽��\n" NOR;
         else if(i==3)  msg = HIY "\n�۴̿ͽ�����-- �������أ�\n" NOR;
         else     {  
                   msg = HIW "\n�۴̿ͽ�����--����-- ͼ��ذ���֣�" NOR;
                       target->receive_wound("sen",extra1/3,me);
                     target->receive_wound("kee",extra1/3,me);
                   //me->receive_heal("kee",extra); // grin�����Լ�����
                  }
        message_vision(msg,me,target);
        if(random((int)me->query("combat_exp")) >(int)target->query("combat_exp")/3)
              {
                msg =HIC"\n�����ˣ�"NOR;
                switch(random(3)) {
                        case 0:{ msg += YEL "$n������������"+ weapon->name()+ YEL "�̸����ţ���Ѫ���ؿ����������\n" NOR;
                                      break;};
                                
                        case 1:{ msg += MAG "գ�ۼ䣬$N���е�"+ weapon->name()+MAG "������Ϣ�ش�����$n��������\n" NOR;
                                      break;};
                                
                        case 2:{ msg += HIM "$nͻȻͷ��һ���ʹ��ԭ����$N���ϵ�"+ weapon->name()+HIM "�ݺݴ��ˣ�\n" NOR;
                                       break;};                               
                              }
                if (extra>(100+dlkm*100)) extra=100+dlkm*100;
                target->receive_damage("kee",extra,me);
              target->receive_wound("kee",extra/2,me);
                message_vision(msg,me,target);  
                COMBAT_D->report_status(target,0);
       } 
       else COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        me->add("force",-100);   
      }
        me->add_temp("apply/attack",-temp_extra/5);
        me->add_temp("apply/damage",-temp_extra/5);
        //me->start_busy(1+random(1));
        return 1;
 }
