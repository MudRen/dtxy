/* Created by emotion
���˵��:
==========
����--
    �����������������ĳɳ��ܵ�������ܹ��ﵽ�ĵȼ�������. һ���µ�����������ϵͳ�к�, ��������ܹ��ﵽ�ĵȼ���ȷ����.
    һ����������ܹ��ﵽ�ĵȼ����ڶ�Ϊ7��. һ������, ��ϵͳ�е�����, ����ǰ�ȼ�����Ϊ1. ����: һ���ռ���������, ����
    ��ǰ�ȼ�Ϊ1, ���ܹ�ͨ�������ﵽ����ߵȼ�Ϊ7.

    ������������һЩ����: damage.
    �����ĵ�ǰ�ȼ�*50Ϊ�����������Ե�ǰ������������ֵ. ����: һ����ǰ�ȼ�Ϊ4������, ����damage��������������4*50=200
    ����������ĳһ����һ��, ��Ҫ���ĸ����Ե�ǰ��ֵ+1Ȼ����ƽ����ô���wx. ������㷨, ���Ҫ��һ�����Դ�1����280, ����
    ��Ҫ7.35Mwx. ÿ���������Եĳɹ���=random(�����ߵ�forge(skill)) > random(���Ե�ǰ��ֵ+1)
    ���������ɹ�����ʧ�ܶ�������wx. ����������������Ժ͸�Ե�ߵĻ�, ��һ���ļ���wx�ķѼ���. ����Ϊ
    random(int+kar+400)<int+kar

    �����ĵ�ǰ������������һ����Ҫ����(��ǰ����+1)*1000��ô����������. ����������ʹ�ø�������ʱ���������������Ҫ�õ�
    (��ǰ����+1)*1000��ô��gold

    ������ʹ���ߵ���϶Ⱦ������������й������Եķ�����. ��϶�=ʹ����ʹ�ø������ľ���/(�������ȼ�*1000). �����������
    ������ʹ�þ�������. �������ת�ø�����, ʹ�þ�������

    �������п�, ����Ƕ��ħ����ʯ. �׵������͸���������ܴﵽ�ĵȼ�һ��. ����һ����ߵȼ����Դﵽ7������, �����䵱ǰ��
    ��ֻ��1, �����ǿ��Ա�Ƕ��7��ħ����ʯ�Լ������й�������

��ʯ--
	����ħ����ʯ��5��(��ľˮ����), ÿ�ֱ�ʯӵ�ж�Ӧ��ħ����������.��ʱ�ʯ�Ǻ������ռ���ʯ, ͬʱ�������е���������.
	��ʯ�ɳ����ܵȼ�����. ������ʯ����������һ����Ҫ���ĸ����Ե�ǰ��ֵ+1Ȼ����ƽ����ô���dx. ��ʱ�ʯ��������2��
	ÿ���������Եĳɹ���=random(�����ߵ�alchemy(skill)) > random(���Ե�ǰ��+1)
    ���������ɹ�����ʧ�ܶ�������dx. ����������������Ժ͸�Ե�ߵĻ�, ��һ���ļ���wx�ķѼ���. ����Ϊ
    random(int+kar+600)<int+kar
    ��ʯһ��Ƕ�������Ͳ������ó���. �˺������������������Խ���ͬʱ����wx��dx, ��ͬʱ�ܵ������ĵȼ�����

����--
==========
*/

#include <dbase.h>
#include <ansi.h>

// ���´����dt2�Ĺ��������newitems.c������
inherit __DIR__"newitemname.c";
string *shuxing=({"str","int","con","cor","cps","per","spi","kar"});
object get_weapon(object me,object killer);
object get_armor(object me,object killer);
object get_baoshi(object me,object killer);
// ���ϴ����dt2�Ĺ��������newitems.c������

int is_newitem() {
	return 1;
}

  // �������Ʒ�Ѿ������˵Ļ�, �ǲ��ᱻ����ʹ�õ�, ���Ŷ���
  // �������˿��԰���Ʒת�ø�����
void init() {
	object env;
	string owner_id;
	env = environment();
	if (!objectp(env))
		return;
	owner_id = query("newitem_owner_id");
	if (stringp(owner_id) && owner_id != env->query("id") ) {
		call_out("self_destruct", 1, env);
	}
}

void self_destruct(object env) {
	tell_object(env, HIC"\nֻ��һ������ƮȻ����, ��������һ���, ��������Ц��: ��������������˵�\nȻ��ץ��"
	                 + query("name") +", ��ʱ�ټ�����\n\n"NOR);
	destruct(this_object());
}


// ���´����dt2�Ĺ��������newitems.c�����������޸�
//added by huarong 2004/11
void setname_weapon(object weapon)
{
     int k,mark;
     string type;
     string temp_name, *temp_id, long;

     type=weapon->query("skill_type");
     k=weapon->query("maximum_level");
     //if (type=="mace") return 0;
     if (random(100)>90) return 0;
	switch(type)
	{
	  case "sword" :
	  	if( weapon->query("anqi/allow") )
	  	{
	  	temp_name=name_qin1[k][0];
	  	temp_name+="��";
		temp_id=({"qin"+random(10000), name_qin1[k][1]+" qin","qin"});
	  	}
	  	else if( random(2) )
	  	{
	  	weapon->set("music/type", "xiao");
	  	temp_name=name_xiao1[k][0];
	  	temp_name+="��";
		temp_id=({"xiao"+random(10000), name_xiao1[k][1]+" xiao","xiao"});	
	  	}
	  	else
	  	{
                if(random(2))
                {
		temp_name=name_sword1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_sword2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"��":"��";
		if(mark==1)
		temp_id=({"sword"+random(10000), name_sword1[k][1]+" sword","sword"});
	        else
		temp_id=({"sword"+random(10000), name_sword2[k][1]+" sword","sword"});
		}
		break;
	  case "blade" :
                if(random(2))
                {
		temp_name=name_blade1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_blade2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+=random(2)?"��":"ն";
		if(mark==1)
		temp_id=({"blade"+random(10000), name_blade1[k][1]+" blade","blade"});
	        else
		temp_id=({"blade"+random(10000), name_blade2[k][1]+" blade","blade"});
		break;
	  case "fork" :
                if(random(2))
                {
		temp_name=name_fork1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_fork2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+="��";
		if(mark==1)
		temp_id=({"fork"+random(10000), name_fork1[k][1]+" fork","fork"});
	        else
		temp_id=({"fork"+random(10000), name_fork2[k][1]+" fork","fork"});
		break;
	  case "stick" :
                if(random(2))
                {
		temp_name=name_stick1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_stick2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"��":"��";
		if(mark==1)
		temp_id=({"stick"+random(10000), name_stick1[k][1]+" stick","stick"});
	        else
		temp_id=({"stick"+random(10000), name_stick2[k][1]+" stick","stick"});
		break;
	  case "whip" :
	       if(random(2))
                {
		temp_name=name_whip3[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_whip4[k][0];
		mark=2;
	        }
		if(k<6) temp_name+=random(2)?"��":"˿";
		else
		  {
                         temp_name+=random(2)?"��":"��";
			 temp_name+="�";
	          }
		if(mark==1)
		temp_id=({"whip"+random(10000), name_whip3[k][1]+" whip","whip"});
	        else
		temp_id=({"whip"+random(10000), name_whip4[k][1]+" whip","whip"});
		break;
	case "mace" :
                if(random(2))
                {
		temp_name=name_whip1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_whip2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"��":"�";
		if(mark==1)
		temp_id=({"mace"+random(10000), name_whip1[k][1]+" mace","mace"});
	        else
		temp_id=({"mace"+random(10000), name_whip2[k][1]+" mace","mace"});
		break;
	  case "hammer" :
                if(random(2))
                {
		temp_name=name_hammer1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_hammer2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+="��";
		if(mark==1)
		temp_id=({"hammer"+random(10000), name_hammer1[k][1]+" hammer","hammer"});
	        else
		temp_id=({"hammer"+random(10000), name_hammer2[k][1]+" hammer","hammer"});
		break;
	  case "spear" :
                if(random(2))
                {
		temp_name=name_spear1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_spear2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"ǹ":"�";
		if(mark==1)
		temp_id=({"spear"+random(10000), name_spear1[k][1]+" spear","spear"});
	        else
		temp_id=({"spear"+random(10000), name_spear2[k][1]+" spear","spear"});
		break;
	  case "staff" :
                if(random(2))
                {
		temp_name=name_staff1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_staff2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+="��";
		if(mark==1)
		temp_id=({"staff"+random(10000), name_staff1[k][1]+" staff","staff"});
	        else
		temp_id=({"staff"+random(10000), name_staff2[k][1]+" staff","staff"});
		break;
	  case "axe" :
                if(random(2))
                {
		temp_name=name_axe1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_axe2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"֮":"��";
		temp_name+="��";
		if(mark==1)
                temp_id=({"axe"+random(10000), name_axe1[k][1]+" axe","axe"});
	        else
                temp_id=({"axe"+random(10000), name_axe2[k][1]+" axe","axe"});
		break;
	   default :
	  	break;
	}
     temp_name=temp_name+""NOR;
     if(temp_name) weapon->set_name(temp_name, temp_id);
}
// ���ϴ����dt2�Ĺ��������newitems.c�����������޸�

// ���´����dt2�Ĺ��������newitems.c�����������޸�
//added by huarong 2004/11
void setname_armor(object armor)
{
     int k,mark;
     string type;
     string temp_name, *temp_id, long;

     type=armor->query("armor_type");
     k=armor->query("maximum_level");
     if (type=="shield") return 0;
	switch(type)
	{
	  case "armor" :
                if(random(2))
                {
		temp_name=name_armor1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_armor2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"��";
		temp_name+=random(2)?"��":"��";
		if(mark==1)
		temp_id=({"armor" + random(10000), name_armor1[k][1]+" armor","armor"});
	        else
		temp_id=({"armor" + random(10000), name_armor2[k][1]+" armor","armor"});
		break;
	  case "cloth" :
	       if(random(2))
	       {
                if(random(2))
                {
		temp_name=name_cloth11[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_cloth12[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"��";
		temp_name+=random(2)?"��":"��";
		if(mark==1)
		temp_id=({"cloth" + random(10000), name_cloth11[k][1]+" cloth","cloth"});
	        else
		temp_id=({"cloth" + random(10000), name_cloth12[k][1]+" cloth","cloth"});
		armor->set("male_only", 1);
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_cloth21[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_cloth22[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"����":"ϼ��";
		else temp_name+=random(2)?"��":"ȹ";
		if(mark==1)
		temp_id=({"cloth" + random(10000), name_cloth21[k][1]+" cloth","cloth"});
	        else
		temp_id=({"cloth" + random(10000), name_cloth22[k][1]+" cloth","cloth"});
		armor->set("female_only", 1);
	       }
		break;
	  case "head" :
	       if(random(2))
	       {
                if(random(2))
                {
		temp_name=name_head11[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_head12[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"֮":"��";
		temp_name+=random(2)?"��":"��";
		if(mark==1)
		temp_id=({"hat" + random(10000), name_head11[k][1]+" hat","hat"});
	        else
		temp_id=({"hat" + random(10000), name_head12[k][1]+" hat","hat"});
		armor->set("male_only", 1);
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_head21[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_head22[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"ħ":"��";
		temp_name+=random(2)?"��":"��";
		if(mark==1)
		temp_id=({"hat" + random(10000), name_head21[k][1]+" hat","hat"});
	        else
		temp_id=({"hat" + random(10000), name_head22[k][1]+" hat","hat"});
		armor->set("female_only", 1);
	       }
		break;
	  case "boots" :
                if(random(2))
                {
		temp_name=name_boots1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_boots2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"ħ";
		temp_name+=random(2)?"ѥ":"Ь";
		if(mark==1)
		  if(random(2)) temp_id=({"boots" + random(10000), name_boots1[k][1]+" boots","boots"});
		  else temp_id=({"shoes" + random(10000), name_boots1[k][1]+" shoes","shoes"});
	        else
		  if(random(2)) temp_id=({"boots" + random(10000), name_boots2[k][1]+" boots","boots"});
		  else temp_id=({"shoes" + random(10000), name_boots2[k][1]+" shoes","shoes"});
		break;
	  case "neck" :
                if(random(2))
                {
		temp_name=name_neck1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_neck2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"�����":"����";
		if(mark==1)
		temp_id=({"neck" + random(10000), name_neck1[k][1]+" neck","neck"});
	        else
		temp_id=({"neck" + random(10000), name_neck2[k][1]+" neck","neck"});
		break;
	  case "wrists" :
                if(random(2))
                {
		temp_name=name_wrists1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_wrists2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"��";
		if(mark==1)
		{
		temp_id=({"wrists" + random(10000), name_wrists1[k][1]+" wrists","wrists"});
		temp_name+="����";
	        }
	        else
	        {
		temp_id=({"wrists" + random(10000), name_wrists2[k][1]+" wrists","wrists"});
		temp_name+="��";
		}
		break;
	  case "finger" :
		temp_name=name_ring[k][0];
                if(k>0 && k<=10) temp_name+="֮��";
                else temp_name+="��";
		temp_id=({"ring" + random(10000), name_ring[k][1]+" ring","ring"});
		break;
	  case "waist" :
		temp_name=name_waist[k][0];
                if(k>0 && k<=10) temp_name+="����";
		if(random(2)) temp_id=({"belt" + random(10000), name_waist[k][1]+" belt","belt"});
		else temp_id=({"waist" + random(10000), name_waist[k][1]+" waist","waist"});
		break;
	  case "surcoat" :
                if(random(2))
                {
		temp_name=name_surcoat1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_surcoat2[k][0];
		mark=2;
	        }
                if(k>0 && k<=10) temp_name+=random(2)?"����":"����";
		if(mark==1)
		temp_id=({"cloak" + random(10000), name_surcoat1[k][1]+" cloak","cloak"});
	        else
		temp_id=({"cloak" + random(10000), name_surcoat2[k][1]+" cloak","cloak"});
		break;
	  case "hands" :
                if(random(2))
                {
		temp_name=name_hands1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_hands2[k][0];
		mark=2;
	        }
                if(k>0 && k<=10) temp_name+=random(2)?"����":"����";
		if(mark==1)
		temp_id=({"gloves" + random(10000), name_hands1[k][1]+" gloves","gloves"});
	        else
		temp_id=({"gloves" + random(10000), name_hands2[k][1]+" gloves","gloves"});
		break;
	  default :
	  	break;
	}
     temp_name=temp_name+""NOR;
     if(temp_name) armor->set_name(temp_name, temp_id);
}
// ���ϴ����dt2�Ĺ��������newitems.c�����������޸�

// ���´����dt2�Ĺ��������newitems.c�����������޸�
object get_item(object me,object killer)
{
	//object item;
      int i,j;
      j=killer->query_temp("mieyao/level");
      if( j < 7 ) return 0;
      switch(random(17-j))
      	{
		case 0:
			return get_weapon(me,killer);break;
		case 1:
	        	return get_armor(me,killer);break;
        	case 2:
       			return get_baoshi(me,killer);break;
        	default: return 0;
	}
}
// ���ϴ����dt2�Ĺ��������newitems.c�����������޸�

// ���´����dt2�Ĺ��������newitems.c�����������޸�
object get_weapon(object me,object killer)
{
	object weapon;
	int i,j,value,zs;
    	int myexp,taexp,exp,max_level,iceblade_flag = 0;
	string att;
	string *file=({
		"/d/obj/newitem/newweapon/qin.c",
		"/d/obj/newitem/newweapon/sword.c",
		"/d/obj/newitem/newweapon/blade.c",
		"/d/obj/newitem/newweapon/fork.c",
		"/d/obj/newitem/newweapon/stick.c",
		"/d/obj/newitem/newweapon/whip.c",
		"/d/obj/newitem/newweapon/hammer.c",
		"/d/obj/newitem/newweapon/spear.c",
		"/d/obj/newitem/newweapon/staff.c",
		"/d/obj/newitem/newweapon/axe.c",
		"/d/obj/newitem/newweapon/mace.c"});
		
	
	mixed *name=({
		({YEL"��ͭ","bronz",3500,2000,100,10}),
		({HIC"����","steel",2500,5000,500,10}),
		({HIB"����","iron",3000,15000,1000,20}),
		({HIY"�ڽ�","gold",4000,25000,2000,20}),
		({HIR"���","gold",4000,25000,4000,30}),
		({HIG"����","jade",2000,50000,10000,40}),
		({HIR"Ѫ��","jade",2000,50000,20000,40}),
		({HIG"����","jade",2000,100000,50000,60}),
		({HIW"�޳�","jade",2000,200000,100000,80})
		});
	mixed *iceblade_name=({
		({WHT"����ŭ��","hfnh"}),
		({WHT"��ѩ����","sxmt"}),
		({WHT"Сѩ����","xxcq"}),
		({WHT"��ë��ѩ","emdx"}),
		({WHT"�������","xtbl"}),
		({HIG"��ѩ�麮","cxsh"}),
		({HIW"Ʈѩ����","pxcy"}),
		({HIG"��մ亮","xkch"}),
		({HIW"�������","hdby"})
		});
	myexp=me->query("daoxing",1)/1000;
	taexp=killer->query("daoxing",1)/1000;
      	if( random(myexp+taexp) < taexp/2 && !wizardp(killer) )//myexp<taexp/1.5 &&
          	return 0;
	//�õ���ɫװ��
	i=random(11);
	weapon=new(file[i]);
	if(i == 2 && random(10) < 4)
		iceblade_flag = 1;
	//�õ������Ĳ���,��Ŀ�����ȡ���ֵ
	zs = killer->query("lunhui_zhuanshi");
	if( !zs && myexp > 20000 )
	{
		myexp = 20000;
	}
	else if( zs < 5 )
	{
		myexp += zs * 10000;
		if( myexp > (zs + 2) * 10000 )
			myexp = (zs + 2) * 10000;
	}
	else
	{
		if( myexp < 150000 )
			myexp += 50000;
	}
		exp=random(myexp);
		if (exp>100000)  i=random(9);
		else if (exp>50000)  i=random(8);
		else if (exp>20000)  i=random(7);
		else if (exp>10000) i=random(6);
		else if (exp>4000) i=random(5);
		else if (exp>2000) i=random(4);
		else if (exp>1000) i=random(3);
		else if (exp>500) i=random(2);
		else  i=0;
		weapon->set("no_break",1);
		weapon->set_name(name[i][0]+weapon->query("name")+NOR,({weapon->query("id") + random(10000), name[i][1]+" "+weapon->query("id"),weapon->query("id")}));
		weapon->set_weight((name[i][2]+weapon->query_weight())/2);
		/*switch(i)
		{
			case 0: att="������ͭ�Ƴɵġ�\n";break;
			case 1: att="���ɰ��������ɵġ�\n";break;
			case 2: att="����ǧ�꺮�����ɵġ�\n";break;
			case 3: att="���������ڽ����ɵġ�\n";break;
			case 4: att="�����Ϲ��������ɵġ�\n";break;
			case 5: att="���ɴ�˵�е�����֮ʯ���ɵġ�\n";break;
                        case 6: att="���ɴ�˵�еĴ�������̫��֮ʯ���ɵġ�\n";break;
		}
        	weapon->set("long",HIG+weapon->query("long")+att+NOR);*/
        	weapon->set("material", name[i][1]);
        	weapon->set("maximum_level", i + 1);//�ȼ� 1��9
        	weapon->set("max_level", i+1);//�ȼ� 1��9
        	weapon->set("level", 1); // ��ǰ�ȼ�1

        	//��������
        	weapon->set("weapon_prop/damage",30+i*15+random((i+1)*5));//������
        	switch(random(5))
        	{
        		case 0:
        			weapon->set("weapon_prop/gold_attack",10+random(i*10));
        			break;
        		case 1:
        			weapon->set("weapon_prop/wood_attack",10+random(i*10));
        			break;
        		case 2:
        			weapon->set("weapon_prop/earth_attack",10+random(i*10));
        			break;
        		case 3:
        			weapon->set("weapon_prop/water_attack",10+random(i*10));
        			break;
        		case 4:
        			weapon->set("weapon_prop/fire_attack",10+random(i*10));
        			break;
        	}
		/*if (random(2100) > 2090) {
			weapon->add("weapon_prop/damage", 30);
			if ( random(500) > 400 )
				weapon->add("weapon_prop/damage", 20);
		}*/
        	weapon->set("sockets/max",random(i+2));//���ű�ʯ��
        	weapon->set("sockets/now",0);
		weapon->set("wield/daoxing",name[i][4]);
		weapon->set("wield/"+shuxing[random(sizeof(shuxing))],name[i][5]/2+1+random(name[i][5]/2));
		//��ֵ
        	value=name[i][3];
        	value+=weapon->query("sockets/max")*2000;
        	value+=weapon->query("weapon_prop/damage")*1000;
        	weapon->set("value", value*(i+1));

    	setname_weapon(weapon);
	if(iceblade_flag == 1)
	{
		weapon->set_name(iceblade_name[i][0]+"��"+NOR,({"blade" + random(10000), iceblade_name[i][1]+" blade","blade"}));
		weapon->set("material", "ice");
	}
     	if (wizardp(this_player()))
     		tell_object(this_player(),HIM+"���ͣ�"+weapon->query("skill_type")+"     ��ߵȼ���"+weapon->query("max_level")+"\n"NOR);
	return weapon;
}
// ���ϴ����dt2�Ĺ��������newitems.c�����������޸�

// ���´����dt2�Ĺ��������newitems.c�����������޸�
object get_armor(object me,object killer)
{
	object armor;
	int i,j,value,a1,a2,a3,bind_pro,bind_type,zs;
	int myexp,taexp,exp;
	string att;
	string *file=({
		"/d/obj/newitem/newarmor/armor.c",
		"/d/obj/newitem/newarmor/boots.c",
		"/d/obj/newitem/newarmor/cloth.c",
		"/d/obj/newitem/newarmor/finger.c",
		"/d/obj/newitem/newarmor/hands.c",
		"/d/obj/newitem/newarmor/head.c",
		"/d/obj/newitem/newarmor/neck.c",
		"/d/obj/newitem/newarmor/shield.c",
		"/d/obj/newitem/newarmor/surcoat.c",
		"/d/obj/newitem/newarmor/waist.c",
		"/d/obj/newitem/newarmor/wrists.c"});
	mixed *name=({
		({HIY"��Ƥ","boa",3000,2000,100,10}),
		({HIR+BLK"�ڽ�","gold",2500,5000,500,10}),
		({CYN"����","crocodile",3000,10000,1000,10}),
		({HIM"����","jade",2500,20000,2000,20}),
		({HIG"����","mammoth",4000,30000,3000,20}),
		({YEL"����","amber",2000,40000,4000,20}),
		({MAG"����","kylin",2500,60000,6000,20}),
		({HIM"���","emerald",2000,80000,8000,30}),
		({HIC"����","dragon",2500,100000,10000,30}),
		({HIY"ˮ��","crystal",1500,120000,20000,40}),
		({HIR"ս��","mars",3000,140000,40000,40}),
		({HIB"���","spirit",1000,160000,60000,60}),
		({HIW"�޵�","sunshine",2000,180000,80000,60}),
		({HIR+BLK"����","dark",1000,200000,100000,80})
		});
	myexp=me->query("combat_exp",1)/1000;
	taexp=killer->query("combat_exp",1)/1000;
      if( random(myexp+taexp) < taexp/2 && !wizardp(killer) )
         return 0;
//�õ���ɫװ��
		i=random(11);
		armor=new(file[i]);
                 if (!armor) return 0;

		//�õ����ߵĲ���,��Ŀ�����ȡ���ֵ
	zs = killer->query("lunhui_zhuanshi");
	if( !zs && myexp > 20000 )
	{
		myexp = 20000;
	}
	else if( zs < 5 )
	{
		myexp += zs * 10000;
		if( myexp > (zs + 2) * 10000 )
			myexp = (zs + 2) * 10000;
	}
	else
	{
		if( myexp < 150000 )
			myexp += 50000;
	}
		exp=random(myexp);
		if (exp>100000)  i=random(14);
		else if (exp>80000) i=random(13);
		else if (exp>60000) i=random(12);
		else if (exp>40000) i=random(11);
		else if (exp>20000) i=random(10);
		else if (exp>10000) i=random(9);
		else if (exp>8000) i=random(8);
		else if (exp>6000) i=random(7);
		else if (exp>4000) i=random(6);
		else if (exp>3000) i=random(5);
		else if (exp>2000) i=random(4);
		else if (exp>1000) i=random(3);
		else if (exp>500) i=random(2);
           	else  i=0;
		//i=6;
		armor->set("no_break",1);//�д����ԣ��������ܱ���ϣ�ͬʱӦ���޸�weapond.c���ɴ�ϱ�����pfm��cast
					//����huntian-hammer,perform break,cast dragonfire,�����perform leiting
		armor->set_name(name[i][0]+armor->query("name")+NOR,({armor->query("id") + random(10000), name[i][1]+" "+armor->query("id"),armor->query("id")}));
		armor->set_weight((name[i][2]+armor->query_weight())/2);
        	armor->set("long","��������������װ�����Ǵ������ε��²��");
        	armor->set("material", name[i][1]);
        	armor->set("maximum_level", i + 1);//�ȼ� 1��14maximum_level
        	armor->set("max_level", i+1);//�ȼ� 1��14
        	armor->set("level",1);

         	//��������
         	switch(random(5))
        	{
        		case 0:
        			armor->set("armor_prop/gold_defense",5+random(i*5));
        			break;
        		case 1:
        			armor->set("armor_prop/wood_defense",5+random(i*5));
        			break;
        		case 2:
        			armor->set("armor_prop/water_defense",5+random(i*5));
        			break;
        		case 3:
        			armor->set("armor_prop/fire_defense",5+random(i*5));
        			break;
        		case 4:
        			armor->set("armor_prop/earth_defense",5+random(i*5));
        			break;
        	}
        	armor->set("armor_prop/armor",15+i*4+random((i + 1)*2));//������
        	if( !armor->is_acc() )
        	{
        		armor->set("sockets/max",1 + random((i+1)/3));//���ű�ʯ��
        		armor->set("sockets/now",0);
        	}
		armor->set("wield/daoxing",name[i][4]);
		armor->set("wield/"+shuxing[random(sizeof(shuxing))],name[i][5]/2+1+random(name[i][5]/2));
		//��ֵ
        	value=name[i][3];
        	value+=armor->query("sockets/max")*2000;
        	value+=armor->query("armor_prop/armor")*1000;
        	armor->set("value", value*((i+1)/2));

		setname_armor(armor);
     if (wizardp(this_player()))
     tell_object(this_player(),HIM+"���ͣ�"+armor->query("armor_type")+"     ��ߵȼ���"+armor->query("max_level")+"\n"NOR);
		return armor;
}
// ���ϴ����dt2�Ĺ��������newitems.c�����������޸�

// ���´����dt2�Ĺ��������newitems.c�����������޸�
object get_baoshi(object me,object killer)
{
	object baoshi;
	int i,j,value,temp,zs;
	int myexp,taexp,exp;
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
    if( random(myexp+taexp) < taexp/2 && !wizardp(killer) )
         return 0;
    zs = killer->query("lunhui_zhuanshi");
    temp = random( 5010 + zs * 10 );
    if ( temp <= 999 )
		baoshi = new("/d/obj/newitem/baoshi/magic_stone1");
	else if ( temp <= 1999 )
		baoshi = new("/d/obj/newitem/baoshi/magic_stone2");
	else if ( temp <= 2999 )
		baoshi = new("/d/obj/newitem/baoshi/magic_stone3");
	else if ( temp <= 3999 )
		baoshi = new("/d/obj/newitem/baoshi/magic_stone4");
	else if ( temp <= 4999 )
		baoshi = new("/d/obj/newitem/baoshi/magic_stone5");
	else {
		baoshi = new("/d/obj/newitem/baoshi/super_magic_stone");
		log_file("magic_stone", "������һ����ʱ�ʯ!\n");
	}
	return baoshi;
}
// ���ϴ����dt2�Ĺ��������newitems.c�����������޸�

// ������Ʒ����
void set_item_attr(string attr, mixed value, object holder) {
	set(attr, value);
	if (!objectp(holder))
		return;
	if (query("newitem_owner_id") == holder->query("id")) {
		holder->set("newitem/" + query("id") + "/attr/" + attr, value);
	}
}

// ��������׼����
int fight_exp_rate() {
	int temp_value;
	object me;
	me = this_object();
	if (me->is_weapon()) {
		temp_value = me->query("fight_exp") * 100 / ( ( me->query("level") + 1 ) * 1000 );
	} else if (me->is_armor()) {
		temp_value = me->query("fight_exp") * 100 / ( ( me->query("level") + 1 ) * 500 );
	} else if (me->is_acc()) {
		temp_value = me->query("fight_exp") * 100 / ( ( me->query("level") + 1 ) * 500 );
	} else
		temp_value = 0;
	if ( temp_value > 100 )
		temp_value = 100;
	return temp_value;
}

// ����������
int op_exp_rate() {
	int temp_value;
	object me;
	me = this_object();
	if ( me->is_weapon() ) {
		temp_value = me->query("op_exp") * 100 / (me->query("level")*me->query("level")*500);
	} else
		temp_value = 0;
	if ( temp_value > 100 )
		temp_value = 100;
	return temp_value;
}
