// ��Canoe �޸� 05-13-2001
// ������Ϊ������ƫ��

#include <ansi.h>
#include "/daemon/skill/eff_msg.h";
inherit SSERVER;

string *xue_name = ({ 
HIR"�͹�Ѩ"NOR,HIR"����Ѩ"NOR,HIR"����Ѩ"NOR,
HIG"��ԪѨ"NOR,HIG"����Ѩ"NOR,HIG"�м�Ѩ"NOR,
HIY"�н�Ѩ"NOR,HIY"��ͻѨ"NOR,HIY"�ٻ�Ѩ"NOR,
HIM"����Ѩ"NOR,HIM"����Ѩ"NOR,HIM"���Ѩ"NOR,
HIW"�Ϲ�Ѩ"NOR,HIW"��ԨѨ"NOR,HIW"�쾮Ѩ"NOR,
HIC"��ȪѨ"NOR,HIC"����Ѩ"NOR,HIC"����Ѩ"NOR,}); 
string *weapon1_name = ({ HIR"����"NOR,HIR"���ֽ�"NOR,HIG"�콣"NOR}); 
string *weapon2_name = ({ HIW"���ֽ���"NOR,HIB"һ������"NOR,HIR"���ν���"NOR}); 
string *weapon3_name = ({ HBRED"ĩ��֮��"NOR,HBGRN"����֮��"NOR,HBBLU"����֮��"NOR}); 

int perform(object me, object target)
{
        int damage, p;
        string msg, dodge_skill,*limbs;
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("["+HIR"Ѫħ����"NOR+"]ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(!wizardp(me)&&me->query("family/family_name")!="�ݿ�ɽ�޵׶�") return notify_fail("����ʶ����?\n");
        if( (int)me->query_skill("qixiu-jian", 1) < 120 )
                return notify_fail("������޽�������������������ʹ��"+HIR"Ѫħ����"NOR+"�ԵУ�\n");
        if( (int)me->query_skill("sword", 1) < 120 )
                return notify_fail("��Ľ���������죬ʹ����"+HIR"Ѫħ����"NOR+"��\n");
        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("����ڹ�������죬ʹ����"+HIR"Ѫħ����"NOR+"��\n");
        if( (int)me->query_skill("parry", 1) < 120 )
                return notify_fail("����мܲ�����죬ʹ����"+HIR"Ѫħ����"NOR+"��\n");
        if(! me->query_temp("weapon") )
                return notify_fail("������ý�����ʹ�á�"+HIR"Ѫħ����"NOR+"����\n");
        if( (int)me->query("max_force") < 1500 )
                return notify_fail("������������Ϊ���㣬ʹ����"+HIR"Ѫħ����"NOR+"��\n");     
        if( (int)me->query("force") < 1000 )
                return notify_fail("�������������㣬ʹ����"+HIR"Ѫħ����"NOR+"��\n");     
        if( me->query_temp("qxj_jianmang"))
                 return notify_fail("���ʹ�꡸"+HIR"Ѫħ����"NOR+"����Ŀǰ��Ѫ��ӿ���޷��ٴ����ã�\n");
        message_vision(HIB "\n$N����һЦ:���˿��ɲ�����!���г���бָ����,��������������â,�ƺ�Ҫ�ٻ�ʲô!\n\n"NOR, me, target); 
        msg = HIG"ͻȻ֮�䣬$N�������Σ�����һ�����������󺮷�ֱ����$n��"NOR+xue_name[random(sizeof(xue_name))]+"��\n"NOR;
        me->set_temp("qxj_jianmang", 1);
        remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
        if (random(me->query_skill("force")) > random(target->query_skill("force") /4)&&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) ){                     
                me->start_busy(1);
                target->start_busy(1); 
                msg += CYN"$n���һ�������в�����$w��������"NOR+xue_name[random(sizeof(xue_name))]+CYN"�Դ���������������һɢ��\n"NOR;
                damage = (int)me->query_skill("sword", 1);       
                damage = damage + random(damage/2);
                if(damage>300) damage=300;
                if(me->query_skill("huntian-qigong",1) > target->query_skill("force",1)
                && me->query("force") > random(target->query("force"))  ) 
                               damage += random(damage)/2;
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage/3);
                p = (int)target->query("kee")*100/(int)target->query("max_kee");

                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg = replace_string(msg, "$w", weapon1_name[random(sizeof(weapon1_name))]);   
                message_vision(msg, me, target);
               target->set_temp("last_damage_from", me);
                me->add("force", -(int)me->query_skill("sword", 1)/2);
                remove_call_out("perform2");
                call_out("perform2", 1, me, target);  

              } 
        else {
                me->start_busy(2+random(2));
                msg += HIY"\n$nȴʶ���ǵ����������,����ԶԶ����һ��.\n" NOR;
                message_vision(msg, me, target);
             }

        return 1;
}

int perform2(object me, object target)
{
        int damage,p;
        string msg, dodge_skill,*limbs,force_skill,force_skill_name,wep;
        if (!me) return 1;
        if(!target) return 1;
        remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
        if(!living(target)) return notify_fail("�����Ѿ�������ս���ˡ�\n");
       if(!objectp(wep = me->query_temp("weapon")) || wep->query("skill_type") != "sword"){
           if(!wep)msg = HIY"$N����������ʧ�������������֮��ɢ��$n�������˿�����\n"NOR;
           else  msg = HIY"$N����"+wep->name()+HIY"��ֹͣ׷����$n����ܲ��Ľ�ĻҲ��֮��ɢ��ѹ����Ȼ���ᣡ\n"NOR;
           message_vision(msg, me, target);
           if(target->is_busy()) target->start_busy(1);
           me->start_busy(1);
           return 1;
           } 
       if (userp(me) && (me->query_skill_mapped("sword") != "qixiu-jian" || me->query_skill_mapped("parry") != "qixiu-jian")){
           message_vision(HIY"$NͻȻ���У�����������ʹ�������޽�����ȫ��ͬ����������\n"NOR,me);
           if(target->is_busy()) target->start_busy(1);
         me->start_busy(1);
             return 1;
              }
        if(!me->is_fighting(target) && !me->is_killing(target->query("id"))){
           if(!living(target)) msg = HIY"$N��м������$nһ�ۣ�������"+wep->name()+HIY"һ���ڣ�������ɢ���Ľ�Ļ��\n"NOR;
           else msg = HIY"$N������"+wep->name()+HIY"���һ�ڣ���Բ��һ��ֹͣ�˹�����\n"NOR;
           if(target->is_busy()) target->start_busy(1);
           message_vision(msg, me, target);
           return 1;
           }           
        if( (int)me->query("force", 1) < 1000 )
           {message_vision(HIY"$N���н���ɬ�ͣ��ղ�һ���̳���Ȼ����������ԭ�������������ˣ�\n"NOR,me);
         if(target->is_busy()) target->start_busy(1);
           me->start_busy(1);
           return 1;
          }
        force_skill = target->query_skill_mapped("force");
        if( !force_skill ) force_skill_name = "�����ڹ�";
        else    if( force_skill=="huntian-qigong" ) force_skill_name = "��������";
        else    if( force_skill=="lengquan-force" ) force_skill_name = "��Ȫ��";
        else    if( force_skill=="lotusforce" ) force_skill_name = "�����ķ�";
        else    if( force_skill=="moonforce" ) force_skill_name = "�¹��ķ�";
        else    if( force_skill=="ningxie-force" ) force_skill_name = "��Ѫ��";
        else    if( force_skill=="wuxiangforce" ) force_skill_name = "С���๦";
        else    if( force_skill=="dragonforce" ) force_skill_name = "�����ķ�";
        else    if( force_skill=="tonsillit" ) force_skill_name = "������";
        else    if( force_skill=="huntian-qigong" ) force_skill_name = "��Ԫ��";
        else    force_skill_name = "�ڹ�";    
        msg = HIG "\n���ţ�$N��ʽһת�������ٱ�,����ǧ���򻯣���������,��ؿ�ʼ�𶯡�\n"NOR;        
        if (random(me->query_skill("force")) > random(target->query_skill("force") /3)&&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) ){            
                me->start_busy(1);
                target->start_busy(1);
                msg += CYN"ֻ��$nһ���Һ�,�����"NOR+xue_name[random(sizeof(xue_name))]+CYN"�ӹ���$n����"NOR+HIR+force_skill_name+NOR+CYN"����Ѫ��Ȼ�޷����ۡ�\n"NOR;
                msg+=HIY"\n��翪ʼŭ��,�����ƺ�������Щ΢��"+HIR+"Ѫ��!!!\n"NOR;
                damage = (int)me->query_skill("sword", 1);       
                damage = random(damage);
                if(damage>500) damage=500;
                if(me->query_skill("huntian-qigong",1) > target->query_skill("force",1)
                && me->query("force") > random(target->query("force"))  ) 
                damage = damage*3/2 + random(damage/2);
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage/3);
                p = (int)target->query("kee")*100/(int)target->query("max_kee");
                msg += "( $n"+eff_status_msg(p)+" )\n";                
                msg = replace_string(msg, "$w", weapon2_name[random(sizeof(weapon2_name))]);
                me->add("force", -(int)me->query_skill("sword", 1)/2);   
               target->set_temp("last_damage_from", me);
                message_vision(msg, me, target);    
        if( (int)me->query_skill("parry", 1) > 199 &&
            (int)me->query_skill("force", 1) > 199 &&
            (int)me->query_skill("sword", 1) > 199 &&
            (int)me->query_skill("qixiu-jian", 1) > 199 &&
            (int)me->query_skill("force", 1) > 199 ) {
                remove_call_out("perform3");
                call_out("perform3", 1, me, target,force_skill_name); 
                }
        } 
        else 
        {
                me->start_busy(2+random(2));
                msg += HIY"\n$n˳������һת�������������Ȼ�������"NOR+HIR"����Ѫ��Ľ�"NOR+HIY".\n" NOR;
                me->add("force", -(int)me->query_skill("sword", 1)/2);    
                message_vision(msg, me, target);    
        }

        return 1;
}
int perform3(object me, object target,string force_skill_name)
{
        int damage , p;
        string msg, weapon,dodge_skill,*limbs,force_skill;
        if (!me) return 1;
        if(!target) return 1;
        remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
        if(!living(target)) return notify_fail("�����Ѿ�������ս���ˡ�\n");
       if(!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
           if(!weapon)msg = HIY"$N����������ʧ��Բת��������Ҳ��֮��ɢ��$n�������˿�����\n"NOR;
           else  msg = HIY"$N����"+weapon->name()+HIY"��ֹͣ׷����$n����ܲ��Ľ�ĻҲ��֮��ɢ��ѹ����Ȼ���ᣡ\n"NOR;
           message_vision(msg, me, target);
           if(target->is_busy()) target->start_busy(1);
           me->start_busy(1);
           remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
           return 1;
           } 
       if (userp(me) && (me->query_skill_mapped("sword") != "qixiu-jian" || me->query_skill_mapped("parry") != "qixiu-jian")){
           message_vision(HIY"$NͻȻ���У����ƽ�Ļ��ʹ�������޽�����ȫ��ͬ����������\n"NOR,me);
           if(target->is_busy()) target->start_busy(1);
         me->start_busy(1);
          remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
              return 1;
              }
        if(!me->is_fighting(target) && !me->is_killing(target->query("id"))){
           if(!living(target)) msg = HIY"$N��м������$nһ�ۣ�������"+weapon->name()+HIY"һ���ڣ�������ɢ���Ľ�Ļ��\n"NOR;
           else msg = HIY"$N������"+weapon->name()+HIY"���һ�ڣ���Բ��һ��ֹͣ�˹�����\n"NOR;
           if(target->is_busy()) target->start_busy(1);
           remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
           message_vision(msg, me, target);
           return 1;
           }           
        if( (int)me->query("force", 1) < 1000 ){
           message_vision(HIY"$N���н���ɬ�ͣ��ղ�һ���̳���Ȼ����������ԭ�������������ˣ�\n"NOR,me);
         if(target->is_busy()) target->start_busy(1);
           me->start_busy(1);
           remove_call_out("remove_effect");
                call_out("remove_effect", 10, me);
           return 1;
          }
        weapon = me->query_temp("weapon");  
        msg = HIW "\nͻȻ,$N���е�"+ weapon->query("name")+ HIW"������Ѫ����ʹ��������һ��Ѫ�����ڿն���.\n"NOR;  
        msg+=HIR"\n���Ϊ֮����,����Ϊ֮��ɫ,�ֲ����������ֽ�������,�����������.\n"NOR; 
            if (random(me->query_skill("force")) > random(target->query_skill("force") /2)&&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /3) ){   
                me->start_busy(1+random(2));
                target->start_busy(1+random(3));
                msg += weapon3_name[random(sizeof(weapon3_name))]+WHT"�̴�$n��"NOR+HIR+force_skill_name+NOR+WHT",����һ��$n��"NOR+HIM"�ֱ�"NOR+WHT"��Ȼ�ʶϣ�"NOR+xue_name[random(sizeof(xue_name))]+WHT"���Դ�������\n"NOR;
                damage = (int)me->query_skill("sword", 1);       
                damage = damage + random(damage*2);
                if(damage>1000) damage=1000;
                if(me->query_skill("huntian-qigong",1) > target->query_skill("huntian-qigong",1)
                && me->query("force") > random(target->query("force"))  ) 
                damage = damage + random(damage*3/2);
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage/3);
                p = (int)target->query("kee")*100/(int)target->query("max_kee");
                 msg += damage_msg(damage, "����");
                msg += "( $n"+eff_status_msg(p)+" )\n";     
                limbs = target->query("limbs");
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg, "$w", weapon->name());   
               target->set_temp("last_damage_from", me);
               me->add("force", -(int)me->query_skill("sword", 1)/2);
        } else 
        {
                me->start_busy(2+random(3));
                target->start_busy(1);
                msg += HIY"\n$nȴʶ������Ѫ��������,������,ȴҲ����һ���亹��\n" NOR;
                me->add("force", -(int)me->query_skill("sword", 1)/2);
        }
       message_vision(msg, me, target); 
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("qxj_jianmang");
        tell_object(me, GRN"\n�㾭��һ��ʱ�������Ϣ���ֿ���ʹ��"NOR+HIR"Ѫħ����"NOR+"�ˡ�\n"NOR); 
}


