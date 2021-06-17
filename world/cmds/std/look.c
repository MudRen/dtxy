// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */

// look.c
// "per" parts modified by none at 96/10/02

#include <room.h>
#include <ansi.h>
#include <armor.h>  // emotion
#include <weapon.h> // emotion

#define MODULED "/u/yekai/zbtz/moduled.c"
inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);

mixed *tianfu = ({
			({"str","��    ��"}),
			({"con","��    ��"}),
			({"spi","��    ��"}),
			({"kar","��    Ե"}),
			({"cps","��    ��"}),
			({"cor","��    ʶ"}),
			({"per","��    ò"}),
			({"int","��    ��"}),
		 });

mapping family=(["����ɽ���Ƕ�":1,
                 "��ɽ��":1,
				 "ˮ�¹�":1,
				 "�Ϻ�����ɽ":1,
                 "��ׯ��":1,
                 "���޵ظ�":-1,
                 "�¹�":1,
                 "��������":1,
                 "��ѩɽ":-1,
                 "�ݿ�ɽ�޵׶�":-1,
                 "��˿��":-1,
                 "������":1,
                 "����ɢ��":-1,
                 "����ɽ���鶴":1,
                 "���ƶ�":-1,
]);

string *per_msg_male1 = ({
HIY "�ٶ���������ˮ�����̷��飬������������Ŀ�⡣\n" NOR,
HIY "˫Ŀ���ǣ�ü�Ҵ��飬�������޲�Ϊ֮�Ķ���\n" NOR,
HIR "�����촽�����˿��Σ���ֹ�������ޡ�\n" NOR,
HIR "��������Ŀ�����ǣ����˹�Ŀ������ \n" NOR,
MAG "�������񣬷�ױ����������������\n" NOR,
 MAG "Ʈ�ݳ������������ס�\n" NOR,
        CYN "����ΰ��Ӣͦ������֮�䣬��ɷ��\n" NOR,
        CYN "����Ӣΰ������������ȷʵ���������\n" NOR,

});

string *per_msg_male2 = ({
        CYN "Ӣ��������������档\n" NOR,
        CYN "��ò���ڣ���Ŀ���ʡ�\n" NOR,
        CYN "��ò���棬���˷��ס�\n" NOR,
YEL "��Բ���������ڷ����Ǹ񲻷���\n" NOR,
RED "üĿ���㣬�����󷽣�һ���˲š�\n" NOR,
RED "˫�۹⻪Ө��͸���������ǵĹ�â��\n" NOR,
});
string *per_msg_male3 = ({
        CYN "��òƽƽ��ûʲô�ÿ��ġ�\n" NOR,
        CYN "��ò�׶��������⡣\n" NOR,
        CYN "�������ۣ��������硣\n" NOR,
HIB "��ü���ۣ�������ߣ�������״�� \n" NOR,
HIB "��ͷ�������Բ��ģ��ֽŶ̴֣����˷�Ц�� \n" NOR,
NOR "��հ��ݣ��ݹ����꣬������̾�� \n" NOR,
});
string *per_msg_male4 = ({
        CYN "����һ�����Ѳ��ۣ��˾˲�����ģ����\n" NOR,
        CYN "��������ģ�һ���޾���ɵ�ģ���� \n" NOR,
        CYN "������֣���ͷ������������˽�ı��ҡ� \n" NOR,
BLU "ü����б����ͷѢ�ţ����������� \n" NOR,
BLU "�������죬������ף�����ޱȡ� \n" NOR,
BLU "�����Ƥ��ͷ���������˲����ٿ��ڶ��ۡ� \n" NOR,
});
string *per_msg_female1 = ({
        CYN "�������ƣ�����ʤѩ����֪�㵹�˶���Ӣ�ۺ��ܡ� \n" NOR,
        CYN "������������Ŀ���飬����һЦ������������Ȼ�Ķ��� \n" NOR,
        CYN "�������֣��������ˣ��������Ҽ������� \n" NOR,
MAG "�������������Ż���ɽ�����˼�֮���ס� \n" NOR,
HIM "������ϼ���������񣬻����������ӡ� \n" NOR,
HIM "�������ɣ���մһ˿�̳��� \n" NOR,
HIM "����"+HIW+"������"+HIM+"�������ƻã��Ѳ����Ƿ������ \n" NOR,

});
string *per_msg_female2 = ({
        CYN "������������ɫ���������˶��ˡ� \n" NOR,
        CYN "���潿�ݻ���¶������ϸ�������̡� \n" NOR,
        CYN "����κ죬�ۺ��ﲨ������Ͷ��֮�䣬ȷ��һ�����ϡ� \n" NOR,
RED "����΢�ᣬ�ŵ��������¿��ˡ� \n" NOR,
RED "�������ģ�����Ө͸��������˼�� \n" NOR,
HIR "��С���磬��������������������ˡ� \n" NOR,
HIR "�������󣬼���ʤѩ��Ŀ����ˮ�� \n" NOR,
HIW "���۰���������ҩ���̣����￴���� \n" NOR,
});
string *per_msg_female3 = ({
        CYN "���㲻�Ͼ������ˣ�Ҳ���м�����ɫ�� \n" NOR,
        CYN "���û��������м�����ɫ��  \n" NOR,
YEL "�䲻���£���Ҳ�׾�����Щ����֮����\n" NOR,
});
string *per_msg_female4 = ({
        CYN "���ñȽ��ѿ��� \n" NOR,
        CYN "���á���������  \n" NOR,
BLU "�������Σ�״��ҹ�档\n" NOR,
BLU "���б�ۣ���ɫ�Ұܣ�ֱ����һ�㡣\n" NOR,
BLU "����ü�������ۣ���Ƥ�Ʒ�������һ�������¡�\n" NOR,
HIB "��С�綹��üëϡ�裬�����צ������������\n" NOR,
HIB "һ�����������һ����û�øС�\n" NOR,
NOR "�������Ƥɫ�ֺڣ���ª������\n" NOR,
NOR "�ɻƿ��ݣ���ɫ���ƣ�����Ů��ζ��\n" NOR,

});

string *per_msg_kid1 = ({
        CYN "��ü���ۣ�����ʮ�㡣\n" NOR,
        CYN "������ã���̬�Ƿ���\n" NOR,
        CYN "�������£�ɫ��������\n" NOR,
});

string *per_msg_kid2 = ({
        CYN "¡����ۣ���ɫ����\n" NOR,
        CYN "�����ལ�����ϲ����\n" NOR,
        CYN "ϸƤ���⣬�ڳ�������\n" NOR,
});

string *per_msg_kid3 = ({
        CYN "����󰫣�ɵ��ɵ����\n" NOR,
        CYN "�ʷ����֣�С��С�ۡ�\n" NOR,
        CYN "��ͷ���ԣ����ֱ��š�\n" NOR,
});

string *per_msg_kid4 = ({
        CYN "��ͷ���ţ����Ƽ��ݡ�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_yao1 = ({
        HIB "������������һ��ɷ����\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_yao2 = ({
        HIB "����Χ����һ�����\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_yao3 = ({
        HIB "����Χ����һ�ź��ơ�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_yao4 = ({
        HIB "����������һ������֮�С�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_yao5 = ({
        HIB "���Ƽд��������޾������˿־������, �ŵ�����ת�������, ����˫���Ѿ�������ʹ���ˡ�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_xian1 = ({
        HIY "�����Գ�һ�����֮����\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_xian2 = ({
        HIY "����Χ����һ��������\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_xian3 = ({
        HIY "���Χ����һ�����ơ�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

string *pos_msg_xian4 = ({
        HIY "����������"HIW"��"HIR"��"HIM"��"HIC"��"HIY"֮�С�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});

// emotion begins
string *pos_msg_xian5 = ({
        HIY "���Ϸ���������, ���˸ж��ý���ס��Ҫ�ݵ��ڵء�\n" NOR,
        CYN "����ľ�������в�ɫ��\n" NOR,
        CYN "��ٲ�������֫���ࡣ\n" NOR,
});
// emotion ends

// snowcat 12/20/97
string ride_suffix (object me)
{
  string ridemsg = 0;
  object ridee = 0;

  ridee = me->ride();
  if (ridee)
    ridemsg = ridee->query("ride/msg")+"��"+ridee->name()+"��";
  return ridemsg;
}

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
   object obj;
   int result;

   if( !arg ) result = look_room(me, environment(me));
   else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
     if( obj->is_character() ) result = look_living(me, obj);
     else result = look_item(me, obj);
   } else result = look_room_item(me, arg);

   return result;
}

int look_room(object me, object env)
{
   int i;
   object *inv;
   mapping exits;
   string str, str1="", *dirs;
   string ridemsg = "";

   if( !env ) {
     write("������ܻ����ɵ�һƬ��ʲôҲû�С�\n");
     return 1;
   }
   str = env->query("short")?(env->query("outdoors")?HIR"��"HIG+(string)env->query("short")+HIR"��"NOR:HIR"��"HIY+(string)env->query("short")+HIR"��"NOR): "";
   if ( wizardp(me) )// || me->query("env/show_path") )
       str += HIW+" - "+file_name(env)+NOR;
   str += "\n    " + (env->query("long")? env->query("long"): "\n") + (env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );
   if( mapp(exits = env->query("exits")) ) {
     dirs = keys(exits);
     for(i=0; i<sizeof(dirs); i++)
        if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
          dirs[i] = 0;
     dirs -= ({ 0 });
     if( sizeof(dirs)==0 )
        str += "    ����û���κ����Եĳ�·��\n";
     else if( sizeof(dirs)==1 )
        str += "    ����Ψһ�ĳ����� " + BOLD + dirs[0] + NOR + "��\n";
     else
        str += sprintf("    �������Եĳ����� " + BOLD + "%s" + NOR + " �� " + BOLD + "%s" + NOR + "��\n",
          implode(dirs[0..sizeof(dirs)-2], "��"), dirs[sizeof(dirs)-1]);
     for (i = 0; i < sizeof(dirs); i++) {
		 if ( i % 2 == 0 )
		 	str += sprintf("\t"BOLD"%-20s"NOR, "(" + dirs[i] + ")" + exits[dirs[i]]->query("short"));
		 else
		 	str += sprintf("\t"BOLD"%s\n"NOR, "(" + dirs[i] + ")" + exits[dirs[i]]->query("short"));
	 }
	 if (i % 2 == 1)
	 	str += "\n";
   }
//   str += env->door_description();

   inv = all_inventory(env);
   i=sizeof(inv);
   while(i--) {
	 string temp;
     if( !me->visible(inv[i]) ) continue;
     if( inv[i]==me ) continue;

     temp = "  " + inv[i]->short();
     if ( wizardp(me) || me->query("env/show_file_name") )
     	temp = temp + "-" + file_name(inv[i]);
     if (ridemsg = ride_suffix(inv[i]))
        str1 = temp + " <"+ridemsg +
          ">\n"+str1;
     else
        str1 = temp + "\n"+str1;
   }

   write(str+str1);
   return 1;
}

int look_item(object me, object obj)
{
   mixed *inv;
//   write(obj->long());
   // begins -- emotion
   string desc, armor_type, weapon_type, special_effects;
   mapping armor_prop, weapon_prop;
   mixed *props;
   int i, weapon_flag, temp_value;
   desc = obj->query("name");
   if ( wizardp(this_player()) || this_player()->query("env/show_file_name"))
   		desc += " - " + file_name(obj) + "\n";
   else
   		desc += "\n";
   desc += "\n" + obj->long() + "\n";
   desc += "��ֵ(" + ( obj->query("value") ? obj->query("value") : obj->value() ) + ")";
   desc += " ����(" + obj->weight() + ")";
   if ( obj->is_newitem() ) {
	   desc += "\n============================================\n";
	   if (obj->is_armor() || obj->is_weapon() || obj->is_acc() ) {
		   desc += sprintf("��ǰ�ȼ�: %6d        ��ߵȼ�: %6d\n", obj->query("level"), obj->query("max_level"));
		   desc += "����׼��: ";
		   if (obj->query("level") >= obj->query("max_level")) {
			   desc += "------";
		   } else {
		   		desc += sprintf("%5d%%", obj->fight_exp_rate() );
		   }
		   if (obj->is_weapon()) {
			   desc += sprintf("        �����̶�: %5d%%", obj->op_exp_rate() );
		   }
		   if( !obj->is_acc() )
		   		desc += sprintf("\n������ʯ: %6d        ������: %6d", obj->query("sockets/now"), obj->query("sockets/max"));
		   if (obj->query("embed_msg"))
		   		desc += "\n����: " + obj->query("embed_msg") + "\n";
		   if (obj->is_weapon()) {
		   		desc += sprintf("\n�����˺�: %6d\n", obj->query("weapon_prop/damage"));
		   		desc += "�����˺�: ";
		   		if (obj->query("weapon_prop/gold_attack"))
		   			desc += HIY"��"NOR"<" + obj->query("weapon_prop/gold_attack") + ">";
		   		if (obj->query("weapon_prop/wood_attack"))
		   			desc += HIG"ľ"NOR"<" + obj->query("weapon_prop/wood_attack") + ">";
		   		if (obj->query("weapon_prop/water_attack"))
		   			desc += HIB"ˮ"NOR"<" + obj->query("weapon_prop/water_attack") + ">";
		   		if (obj->query("weapon_prop/fire_attack"))
		   			desc += HIR"��"NOR"<" + obj->query("weapon_prop/fire_attack") + ">";
		   		if (obj->query("weapon_prop/earth_attack"))
		   			desc += YELGRN"��"NOR"<" + obj->query("weapon_prop/earth_attack") + ">";
		   		desc += "\n";
			}
		   	else {
		   		desc += sprintf("\n�������: %6d\n", obj->query("armor_prop/armor"));
		   		desc += "���з���: ";
		   		if (obj->query("armor_prop/gold_defense"))
		   			desc += HIY"��"NOR"<" + obj->query("armor_prop/gold_defense") + ">";
		   		if (obj->query("armor_prop/wood_defense"))
		   			desc += HIG"ľ"NOR"<" + obj->query("armor_prop/wood_defense") + ">";
		   		if (obj->query("armor_prop/water_defense"))
		   			desc += HIB"ˮ"NOR"<" + obj->query("armor_prop/water_defense") + ">";
		   		if (obj->query("armor_prop/fire_defense"))
		   			desc += HIR"��"NOR"<" + obj->query("armor_prop/fire_defense") + ">";
		   		if (obj->query("armor_prop/earth_defense"))
		   			desc += YELGRN"��"NOR"<" + obj->query("armor_prop/earth_defense") + ">";
		   		desc += "\n";
			}

	   } else {
		   		desc += "��������: ";
		   		if (obj->query("effect/gold"))
		   			desc += HIY"��"NOR"<" + obj->query("effect/gold") + ">";
		   		if (obj->query("effect/wood"))
		   			desc += HIG"ľ"NOR"<" + obj->query("effect/wood") + ">";
		   		if (obj->query("effect/water"))
		   			desc += HIB"ˮ"NOR"<" + obj->query("effect/water") + ">";
		   		if (obj->query("effect/fire"))
		   			desc += HIR"��"NOR"<" + obj->query("effect/fire") + ">";
		   		if (obj->query("effect/earth"))
		   			desc += YELGRN"��"NOR"<" + obj->query("effect/earth") + ">";
		   		desc += "\n";
	   }
	   if( obj->query("wield/daoxing") )
	   {
		   desc += "װ��Ҫ��\n";
		   desc += "��    �У�" + chinese_number(obj->query("wield/daoxing")) + "��\n";
		   /*desc += "��    �У�" + chinese_number(obj->query("wield/daoxing")) + "��        ";
		   for(i=0;i<sizeof(tianfu);i++)
		   {
		   	if( obj->query("wield/"+tianfu[i][0]) > 0 )
		   		desc += tianfu[i][1] + "��"+obj->query("wield/"+tianfu[i][0]);
		   }
		   desc += "\n";*/
	   }
	   desc += "============================================\n";
	   if (obj->query("mod"))
			desc += MODULED->print_mod(obj,me);
	   me->start_more(desc);
   } else {
	   if ( mapp(armor_prop = obj->query("armor_prop") ) && armor_type = obj->query("armor_type") ) {
		   desc += "  ����װ����λ(";
		   switch (armor_type) {
			   case TYPE_HEAD:
				   desc += "ͷ";
				   break;
			   case TYPE_NECK:
				   desc += "��";
				   break;
			   case TYPE_CLOTH:
				   desc += "��";
				   break;
			   case TYPE_ARMOR:
				   desc += "����";
				   break;
			   case TYPE_SURCOAT:
				   desc += "����";
				   break;
			   case TYPE_WAIST:
				   desc += "��";
				   break;
			   case TYPE_WRISTS:
				   desc += "��";
				   break;
			   case TYPE_SHIELD:
				   desc += "��";
				   break;
			   case TYPE_FINGER:
				   desc += "��ָ";
				   break;
			   case TYPE_HANDS:
				   desc += "��";
				   break;
			   case TYPE_BOOTS:
				   desc += "��";
				   break;
			   case "bandage":
				   desc += "�˿�";
				   break;
			   default:
				   desc += "��֣���Ȼ��֪��(" + armor_type + ")";
		   }
		   desc += ") Ч��(";
		   props = keys( armor_prop );
		   for ( i = 0; i < sizeof( props ); i++ ) {
			   desc += " " + props[ i ] + "(" + armor_prop[ props[ i ] ] + ")";
		   }
		   desc += " )";
	   }

		  if ( mapp(weapon_prop = obj->query("weapon_prop") ) ) {
			  weapon_flag = obj->query("flag");
			  desc += "  ��������(";
			  if ( weapon_flag & TWO_HANDED ) {
				  desc += " ˫��";
			  }
			  if ( weapon_flag & SECONDARY ) {
				  desc += " �������ڶ�����";
			  }
			  if ( weapon_flag & EDGED ) {
				  desc += " �е��е�";
			  }
			  if ( weapon_flag & POINTED ) {
				  desc += " ���";
			  }
			  if ( weapon_flag & LONG ) {
				  desc += "������";
			  }
			  desc += " )";

			  desc += " ����(" + obj->query("skill_type") + ")";

		   desc += " Ч��(";
		   props = keys( weapon_prop );
		   for ( i = 0; i < sizeof( props ); i++ ) {
			   desc += " " + props[ i ] + "<" + weapon_prop[ props[ i ] ] + ">";
		   }
		   desc += " )";
	   }

	   desc += " ����Ч��(";
	   if ( special_effects = obj->query("special_effects") ) {
		   desc += special_effects;
	   } else {
		   desc += "��δ�ṩ˵��";
	   }
	   desc += ")";
	   if (obj->query("rzr_victim_num"))
			desc += "\n" + HIR"������������" + obj->query("rzr_victim_num") + "���ܺ��ߵ���Ѫ����"NOR;
	   //  ends -- emotion
	   me->start_more(desc);
	   inv = all_inventory(obj);
	   if( sizeof(inv) ) {
		 inv = map_array(inv, "inventory_look", this_object() );
		 message("vision", sprintf("�����У�\n  %s\n",
			implode(inv, "\n  ") ), me);
	   }
   }
   return 1;
}
string pos_status_msg(int position)
{
  // beeby 7/14/2000
  if (position == 0) {  // emotion
	  return "����������������";  // emotion
  } else if (position>0)
  {
     if (position<1000)  // emotion
	return (pos_msg_xian1[0]);
     else if (position<100000)  // emotion
         return (pos_msg_xian2[0]);
     else if (position<1000000)  // emotion
        return (pos_msg_xian3[0]);
     else if (position < 3456000 ) // emotion
        return (pos_msg_xian4[0]);
     else
        return (pos_msg_xian5[0]);
  } else
    {
     if (position>-1000) // emotion
        return (pos_msg_yao1[0]);
     else if (position>-100000)  // emotion
         return (pos_msg_yao2[0]);
     else if (position>-1000000)  // emotion
        return (pos_msg_yao3[0]);
     else if (position>-3456000) // emotion
        return (pos_msg_yao4[0]);
     else
        return (pos_msg_yao5[0]);
    }
}
string per_status_msg(int age, int per, string gender)
{
   // added by snowcat
   if (age < 14) {
     if ( per>=25 )
        return ( per_msg_kid1[random(sizeof(per_msg_kid1))]);
     else if ( per>=20 )
        return ( per_msg_kid2[random(sizeof(per_msg_kid2))]);
     else if ( per>=15 )
        return ( per_msg_kid3[random(sizeof(per_msg_kid3))]);
     else    return ( per_msg_kid4[random(sizeof(per_msg_kid4))]);
     }

   if ( gender == "����" ) {
     if ( per>=25 )
        return ( per_msg_male1[random(sizeof(per_msg_male1))]);
     else if ( per>=20 )
        return ( per_msg_male2[random(sizeof(per_msg_male2))]);
     else if ( per>=15 )
        return ( per_msg_male3[random(sizeof(per_msg_male3))]);
     else    return ( per_msg_male4[random(sizeof(per_msg_male4))]);
     }

   if ( gender == "Ů��" ) {
     if ( per>=25 )
                        return ( per_msg_female1[random(sizeof(per_msg_female1))]);
                else if ( per>=20 )
                        return ( per_msg_female2[random(sizeof(per_msg_female2))
]);
                else if ( per>=15 )
                        return ( per_msg_female3[random(sizeof(per_msg_female3))
]);
         else   return ( per_msg_female4[random(sizeof(per_msg_female4))]);
                }
   else return "";
//   else return "����������ûʲô���\n";
}

int look_living(object me, object obj)
{
   string str, limb_status, ridemsg, pro;
   mixed *inv;
   mapping my_fam, fam;
// added for bian by mon.
        mapping ofamily;
   string ogender,orace;
   int oage;

   if(obj->query_temp("d_mana")>0) {
     ofamily=obj->query_temp("family");
     ogender=obj->query_temp("gender");
     orace=obj->query_temp("race");
     oage=obj->query_temp("age");
        } else {
     ofamily=obj->query("family");
     ogender=obj->query("gender");
     orace=obj->query("race");
     oage=obj->query("age");
//fake_age is set as the age when player gets dao-xing:�����ֻء�
//so later on, he/she always looks like the age of that time:)
//but need a "look" to activate all the relatived settings...weiqi
//only when one is not in the status of "bian", check his/her
//fake_age. mon 9/4/97
     if(obj->query("always_young") ) {
        if(oage>obj->query("fake_age")) {
        //if "age" is less than fake_age, reset fake_age.
        //mon 9/4/97
     oage=obj->query("fake_age");
             } else {
               obj->set("fake_age", oage);
        }
     }
     else{
     if(obj->query("combat_exp") > 729000){
obj->set("always_young", 1);
obj->set("fake_age", oage);
     }
     }
//done with fake_age.
        }


   if( me!=obj && obj->visible(me) )
     message("vision", me->name() + "�������㿴����֪����Щʲô���⡣\n", obj);

   str = obj->long();

   str = replace_string(str, "$n", me->name());
   str = replace_string(str, "$N", obj->name());
    str = replace_string(str, "$C", RANK_D->query_respect(obj));
    str = replace_string(str, "$c", RANK_D->query_rude(obj));
   str = replace_string(str, "$R", RANK_D->query_respect(me));
   str = replace_string(str, "$r", RANK_D->query_rude(me));


   pro = (obj==me) ? gender_self(ogender) : gender_pronoun(ogender);

        if(obj->query_temp("d_mana")==0 || obj->query_temp("is_character")) {

   if( orace=="����"
   &&   intp(oage) )
     if(oage<10) {
        str += sprintf("%s��������Ȼ������ʮ�ꡣ\n", pro);
     }
     else{
        str += sprintf("%s������Լ%s���ꡣ\n", pro, chinese_number(oage / 10 * 10));
     }

   //check about wife and husband
   if((obj->parse_command_id_list())[0]==me->query("couple/id") ) {
     if( (string)me->query("gender")=="Ů��" ){
     str += sprintf("%s������ɷ�\n", pro);
     }
     else{
        str += sprintf("%s��������ӡ�\n", pro);
     }
   }
   // If we both has family, check if we have any relations.
   if( obj!=me
   &&   mapp(fam = ofamily)
   &&   mapp(my_fam = me->query("family"))
   &&   fam["family_name"] == my_fam["family_name"] ) {

     if( fam["generation"]==my_fam["generation"] ) {
        if( ogender == "����" )
          str += sprintf( pro + "�����%s%s��\n",
             my_fam["master_id"] == fam["master_id"] ? "": "ͬ��",
             my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
        else
          str += sprintf( pro + "�����%s%s��\n",
             my_fam["master_id"] == fam["master_id"] ? "": "ͬ��",
             my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
     } else if( fam["generation"] < my_fam["generation"] ) {
        if( member_array(my_fam["master_id"],
            obj->parse_command_id_list())>-1  )
          str += pro + "�����ʦ����\n";
        else if( my_fam["generation"] - fam["generation"] > 1 )
          str += pro + "�����ͬ�ų�����\n";
        else if( fam["enter_time"] < my_fam["enter_time"] )
          str += pro + "�����ʦ����\n";
        else
          str += pro + "�����ʦ�塣\n";
     } else {
        if( fam["generation"] - my_fam["generation"] > 1 )
          str += pro + "�����ͬ������\n";
        else if( fam["master_id"] == me->query("id") )
          str += pro + "����ĵ��ӡ�\n";
        else
          str += pro + "�����ʦֶ��\n";
     }
   }

/*   if( obj->query("max_kee") )
     str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";
*/

//here, if per>=100, no rong-mao description, it'll be necessary sometimes.
//return special looking first if he/she has one.

   if( obj->query("looking") ){
     str += pro + (string)obj->query("looking") + "\n";
   } else {
     string looking= per_status_msg((int)obj->query("age"),
            (int)obj->query_per(), ogender);
              if( strlen(looking)>1 && obj->query("per") < 100 )
                    str += pro + looking;
   }

   ridemsg = ride_suffix(obj);
   if (ridemsg)
     str += pro + "��" + ridemsg + "��\n";

// Beeby 7/14/2000
// show position
//   str += pro + pos_status_msg(obj->query("position"))+"\n";
   str += pro; // emotion
   if (obj->query("yaoorxian")) // emotion
       str += pos_status_msg(obj->query("yaoorxian") * obj->query( "daoxing" ) )+"\n";  // emotion
   else
       str += pos_status_msg(family[obj->query("family/family_name")] * obj->query( "daoxing" ) )+"\n";  // emotion
   inv = all_inventory(obj);
   if( sizeof(inv) ) {
     inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
     inv -= ({ 0 });
     if( sizeof(inv) )
        str += sprintf( obj->is_corpse() ? "%s�������У�\n%s\n" : "%s���ϴ��ţ�\n%s\n",          pro, implode(inv, "\n") );
   }

   }

        me->start_more(str);

   if( obj!=me
   &&   living(obj)
   &&   random((int)obj->query("bellicosity")/10) > (int)me->query_per() ) {
     write( obj->name() + "ͻȻת��ͷ������һ�ۡ�\n");
     COMBAT_D->auto_fight(obj, me, "berserk");
     return 1;
   }

//this part is  taken from attack.c
//mon 1/22/98
/*
   if( obj!=me
   && living(obj)
   && userp(obj)
        && random((int)obj->query("bellicosity")/40) > (int)obj->query("cps") )
     COMBAT_D->auto_fight(obj, me, "berserk");
*/

   return 1;
}

string inventory_look(object obj, int flag)
{
   string str;

   str = obj->short();
   if ( wizardp(this_player()) || this_player()->query("env/show_file_name"))
   		str += " - " + file_name(obj);
   if( obj->query("equipped") )
     str = HIC "  ��" NOR + str;
   else if( !flag )
     str = "    " + str;
   else
     return 0;

   if (obj->is_newitem() && obj->query("newitem_owner_id"))
   		str += HIC"<��ע��>"NOR;

   return str;
}

int look_room_item(object me, string arg)
{
   object env;
   mapping item, exits;

   if( !objectp(env = environment(me)) )
     return notify_fail("����ֻ�л����ɵ�һƬ��ʲôҲû�С�\n");

   if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
     if( stringp(item[arg]) )
        write(item[arg]);
     else if( functionp(item[arg]) )
        write((string)(*item[arg])(me));

     return 1;
   }
   if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
     if( objectp(env = load_object(exits[arg])) )
        look_room(me, env);
     else {
       return notify_fail("��ʲôҲ��������\n");
     }
     return 1;
   }
  return notify_fail("��Ҫ��ʲô��\n");
}

int help (object me)
{
   write(@HELP
ָ���ʽ: look [<��Ʒ>|<����>|<����>]

���ָ������鿴�����ڵĻ�����ĳ����Ʒ��������Ƿ���

HELP
);
   return 1;
}
