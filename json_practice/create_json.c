#include<stdio.h>
#include<stdlib.h>
#include "cJSON.h"

int main()
{
	cJSON *student = cJSON_CreateObject();

	cJSON_AddStringToObject(student, "Name", "Jessica");
	cJSON_AddStringToObject(student, "Class", "VIII A");
	cJSON_AddStringToObject(student, "USN", "4SO21CS066");

	//skills
	cJSON *skills = cJSON_CreateObject();
	//categorize skills
	cJSON *programming_languages = cJSON_CreateArray();
	cJSON_AddItemToArray(programming_languages, cJSON_CreateString("C"));
	cJSON_AddItemToArray(programming_languages, cJSON_CreateString("Python"));

	cJSON *networking = cJSON_CreateArray();
	cJSON_AddItemToArray(networking, cJSON_CreateString("Networking Protocols"));
	cJSON_AddItemToArray(networking, cJSON_CreateString("Wireshark"));
	cJSON_AddItemToArray(networking, cJSON_CreateString("Firewalls"));
	cJSON_AddItemToArray(networking, cJSON_CreateString("Wi-Fi Technology"));

	cJSON_AddItemToObject(skills, "Programming Languages", programming_languages);
	cJSON_AddItemToObject(skills, "Networking Concepts", networking);

	//internships
	cJSON *internships = cJSON_CreateObject();
	cJSON_AddStringToObject(internships, "Organization", "VVDN Technologies");
	cJSON_AddStringToObject(internships, "Department", "Networking and Wi-Fi");
	cJSON *skill = cJSON_CreateArray();
	cJSON_AddItemToArray(skill, cJSON_CreateString("Networking Concepts"));
	cJSON_AddItemToArray(skill, cJSON_CreateString("Wi-Fi Technology"));
	cJSON_AddItemToArray(skill, cJSON_CreateString("Linux(Ubuntu)"));
	cJSON_AddItemToObject(internships, "Skills Gained", skill);
	cJSON_AddStringToObject(internships, "Duration", "5 months");

	cJSON_AddItemToObject(student, "Skills", skills);
	cJSON_AddItemToObject(student, "Internship", internships);

	char *json = cJSON_Print(student);
	printf("Generated JSON:\n%s\n", json);

	free(json);
	cJSON_Delete(student);

	return 0;
}
