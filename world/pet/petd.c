// 2001-06-10 By canoe
// ��,ľ,ˮ,��,��,ʥ ��������

#include <ansi.h>
mapping table=([
	// ��,ľ,ˮ,��,��,
	"��": ({"ľ"}),
	"ľ": ({"ˮ"}),
	"ˮ": ({"��"}),
	"��": ({"��"}),
	"��": ({"��"}),
	]);
string *suss=({
        "\n$N"HIY"����ϼ��һ��,$n��ʱ�ۻ����ҡ�"NOR,
        "\n$N"HIR"����һ��,���Է��ӵ����쾡�¡�"NOR,
        "\n$N"HIB"�����һ��,$n��Ȼ���Ժ����ز�֪���ֿ���"NOR,
         });
int count(object attacker, object target)
{       
        string att_shuxing,tar_shuxing;// attacker,target������
	int result=1;
	att_shuxing=attacker->query("shuxing");
	tar_shuxing=target->query("shuxing");
	if(userp(target)) return 1; // ��player����Ч������
       if((random(attacker->query("combat_exp"))<random(target->query("combat_exp")))&&!userp(target))
       // ����ս���Ӿ���
       {
       attacker->add("combat_exp",random(50));
       attacker->add("daoxing",random(50));
       }
       //����ʥ���� 
       if (attacker->query("shuxing")=="ʥ"&&target->query("shuxing")!="ʥ")  // attacker ��ʥ,target����
         {
              message_vision(suss[random(sizeof(suss))],attacker,target);
              result/=100*(random(150)+150);     // damage * 2.25     
              return result;
         }
       else if (!target->query("shuxing"))
	{
	message_vision(suss[random(sizeof(suss))],attacker,target);
	 return 2*result; // ��npc Ч��*2 
        }
     	//��npc������*2,
	else if(member_array(att_shuxing, table[tar_shuxing])>-1)  // target ���� attacker.
         {
         	message_vision(suss[random(sizeof(suss))],attacker,target);
         	result/=100*(random(100)+100);	// damage * 1.5	
         }	
	else if(member_array(tar_shuxing, table[att_shuxing])>-1) //attacker ���� target.
	 {
	 	message_vision(suss[random(sizeof(suss))],attacker,target);
	 	result/=100*(random(50)+50);      // damage * 0.75
         }
        return result;
}
