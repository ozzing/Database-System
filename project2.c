#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

#define MAX 0xffff

const char* host = "localhost";
const char* user = "project";
const char* pw = "project";
const char* db = "project";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	FILE* fin = fopen("project2.txt", "r");

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		char* init = (char*)malloc(sizeof(char) * MAX);
		int i = 0;
		while(!feof(fin)) {
			i++;
			fgets(init, MAX, fin);
			if (mysql_query(connection, init)!=0) {
				printf("%d : ", i);
				printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
				return 1;
			}
		}
		while (1) {
			int op, arg = 0;
			char tr;
			char* query = (char*)malloc(sizeof(char) * MAX);
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			scanf("%d", &op);
			scanf("%c", &tr);
			if (op == 0) break;
			else if (op == 1) {
				arg = 6;
				char* k = (char*)malloc(sizeof(char) * 5);
				char* brand = (char*)malloc(sizeof(char) * 30);
				printf("\n\n");
				printf("---- TYPE 1 ----\n\n");
				printf("** Show sales trends for a particular brand over the past k years. **\n");
				printf(" Which brand? (e.g. Ford) : ");
				gets(brand);
				printf(" Which k? : ");
				gets(k);
				strcpy(query, "select brand.name, sale.* from sale join vehicle on vehicle.VIN=sale.VIN inner join model on model.m_id=vehicle.m_id inner join brand on brand.b_id=model.b_id inner join customer on customer.c_id=sale.c_id where year(date(now())) - year(date) < ");
				strcat(query, k);
				strcat(query, " and brand.name='");
				strcat(query, brand);
				strcat(query, "' order by date asc");
				printf("\n");

				if (arg != 0) {
					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							for (int i = 0; i < arg; i++) {
								printf("%s\t", sql_row[i]);
							}
							printf("\n");
						}
						printf("\n\n");
						mysql_free_result(sql_result);
					}
				}

				printf("------- Subtypes in TYPE 1 -------\n\n");
				printf("\t1. TYPE 1-1\n");
				printf("\t0. QUIT\n");
				scanf("%d", &op);
				scanf("%c", &tr);

				if (op == 1) {
					arg = 7;
					printf("\n\n");
					printf("---- TYPE 1-1 ----\n\n");
					printf("** Then break these data out by gender of the buyer. **\n");

					strcpy(query, "select gender, brand.name, sale.* from sale join vehicle on vehicle.VIN=sale.VIN inner join model on model.m_id=vehicle.m_id inner join brand on brand.b_id=model.b_id inner join customer on customer.c_id=sale.c_id where year(date(now())) - year(date) < ");
					strcat(query, k);
					strcat(query, " and brand.name='");
					strcat(query, brand);
					strcat(query, "' and gender!='Non-binary' order by gender asc");
					printf("\n");
				}
				else {
					arg = 0;
					if (op == 0) printf("\n\n");
					else printf("\nwrong input\n\n");
				}

				if (arg != 0) {
					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							for (int i = 0; i < arg; i++) {
								printf("%s\t", sql_row[i]);
							}
							printf("\n");
						}
						printf("\n\n");
						mysql_free_result(sql_result);
					}
				}

				printf("------- Subtypes in TYPE 1-1 -------\n\n"); // �Ѵ� ���ص� �Ǵ���?
				printf("\t1. TYPE 1-1-1\n");
				printf("\t0. QUIT\n");
				scanf("%d", &op);
				scanf("%c", &tr);

				if (op == 1) {
					arg = 8;
					printf("\n\n");
					printf("---- TYPE 1-1-1 ----\n\n");
					printf("** Then by income range. **\n");

					strcpy(query, "select gender, income, brand.name, sale.* from sale join vehicle on vehicle.VIN=sale.VIN inner join model on model.m_id=vehicle.m_id inner join brand on brand.b_id=model.b_id inner join customer on customer.c_id=sale.c_id where year(date(now())) - year(date) < ");
					strcat(query, k);
					strcat(query, " and brand.name='");
					strcat(query, brand);
					strcat(query, "' and gender!='Non-binary' order by gender asc, income desc");
					printf("\n");
				}
				else {
					arg = 0;
					if (op == 0) printf("\n\n");
					else printf("\nwrong input\n\n");
				}

			}
			else if (op == 2) {
				arg = 6;
				char* k = (char*)malloc(sizeof(char) * 5);
				printf("\n\n");
				printf("---- TYPE 2 ----\n\n");
				printf("** Show sales trends for various brands over the past k years. **\n");
				printf(" Which k? : ");
				gets(k);
				strcpy(query, "select brand.name, sale.* from sale join vehicle on vehicle.VIN=sale.VIN inner join model on model.m_id=vehicle.m_id inner join brand on brand.b_id=model.b_id inner join customer on customer.c_id=sale.c_id where year(date(now())) - year(date) < ");
				strcat(query, k);
				strcat(query, " order by brand.name asc");
				printf("\n");

				if (arg != 0) {
					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							for (int i = 0; i < arg; i++) {
								printf("%s\t", sql_row[i]);
							}
							printf("\n");
						}
						printf("\n\n");
						mysql_free_result(sql_result);
					}
				}

				printf("------- Subtypes in TYPE 2 -------\n\n");
				printf("\t1. TYPE 2-1\n");
				printf("\t0. QUIT\n");
				scanf("%d", &op);
				scanf("%c", &tr);

				if (op == 1) {
					arg = 7;
					printf("\n\n");
					printf("---- TYPE 2-1 ----\n\n");
					printf("** Then break these data out by gender of the buyer. **\n");
					strcpy(query, "select gender, brand.name, sale.* from sale join vehicle on vehicle.VIN=sale.VIN inner join model on model.m_id=vehicle.m_id inner join brand on brand.b_id=model.b_id inner join customer on customer.c_id=sale.c_id where year(date(now())) - year(date) < ");
					strcat(query, k);
					strcat(query, " and gender!='Non-binary' order by gender asc");
					printf("\n");
				}
				else {
					arg = 0;
					if (op == 0) printf("\n\n");
					else printf("\nwrong input\n\n");
				}

				if (arg != 0) {
					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							for (int i = 0; i < arg; i++) {
								printf("%s\t", sql_row[i]);
							}
							printf("\n");
						}
						printf("\n\n");
						mysql_free_result(sql_result);
					}
				}

				printf("------- Subtypes in TYPE 2-1 -------\n\n"); // �Ѵ� ���ص� �Ǵ���?
				printf("\t1. TYPE 2-1-1\n");
				printf("\t0. QUIT\n");
				scanf("%d", &op);
				scanf("%c", &tr);

				if (op == 1) {
					arg = 8;
					printf("\n\n");
					printf("---- TYPE 2-1-1 ----\n\n");
					printf("** Then by income range. **\n");

					strcpy(query, "select gender, income, brand.name, sale.* from sale join vehicle on vehicle.VIN=sale.VIN inner join model on model.m_id=vehicle.m_id inner join brand on brand.b_id=model.b_id inner join customer on customer.c_id=sale.c_id where year(date(now())) - year(date) < ");
					strcat(query, k);
					strcat(query, " and gender!='Non-binary' order by gender asc, income desc");
					printf("\n");
				}
				else {
					arg = 0;
					if (op == 0) printf("\n\n");
					else printf("\nwrong input\n\n");
				}
			}
			else if (op == 3) {
				arg = 3;
				char* k = (char*)malloc(sizeof(char) * 5);
				char* sdate = (char*)malloc(sizeof(char) * 10);
				char* edate = (char*)malloc(sizeof(char) * 10);
				char* supp = (char*)malloc(sizeof(char) * 30);
				printf("\n\n");
				printf("---- TYPE 3 ----\n\n");
				printf("** Find that transmissions made by supplier (company name) between two given dates are defective. **\n");
				printf(" Which supplier? (e.g. Keeling-Stiedemann) : ");
				gets(supp);
				printf(" Which start-date? (YYYY-MM-DD) : ");
				gets(sdate);
				printf(" Which end-date? (YYYY-MM-DD) : ");
				gets(edate);
				strcpy(query, "select supplier.name, vehicle.transmission, s_date from vehicle join supplier on supplier.s_id=vehicle.s_id join sale on vehicle.VIN = sale.VIN where date_format(s_date, '%Y-%m-%d') > '");
				strcat(query, sdate);
				strcat(query, "' and date_format(s_date, '%Y-%m-%d') < '");
				strcat(query, edate);
				strcat(query, "' and supplier.name = '");
				strcat(query, supp);
				strcat(query, "'");
				printf("\n");

				if (arg != 0) {
					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							for (int i = 0; i < arg; i++) {
								printf("%s\t", sql_row[i]);
							}
							printf("\n");
						}
						printf("\n\n");
						mysql_free_result(sql_result);
					}
				}

				printf("------- Subtypes in TYPE 3 -------\n\n"); // �Ѵ� ���ص� �Ǵ���?
				printf("\t1. TYPE 3-1\n");
				printf("\t2. TYPE 3-2\n");
				printf("\t0. QUIT\n");
				scanf("%d", &op);
				scanf("%c", &tr);

				if (op == 1) {
					printf("\n\n");
					printf("---- TYPE 3.1 ----\n\n");
					printf("** Find the VIN of each car containing such a transmission and the customer to which it was sold. **\n");

					strcpy(query, "select vehicle.VIN, customer.name, vehicle.transmission from vehicle join supplier on supplier.s_id=vehicle.s_id join sale on vehicle.VIN=sale.VIN join customer on sale.c_id=customer.c_id where date_format(s_date, '%Y-%m-%d') > '");
					strcat(query, sdate);
					strcat(query, "' and date_format(s_date, '%Y-%m-%d') < '");
					strcat(query, edate);
					strcat(query, "' and supplier.name = '");
					strcat(query, supp);
					strcat(query, "'");
					printf("\n");
				}
				else if (op == 2) {
					printf("\n\n");
					printf("---- TYPE 3.2 ----\n\n");
					printf("** Find the dealer who sold the VIN and transmission for each vehicle containing these transmissions. **\n");

					strcpy(query, "select vehicle.dealer, vehicle.VIN, vehicle.transmission from vehicle join supplier on supplier.s_id=vehicle.s_id join sale on vehicle.VIN=sale.VIN join customer on sale.c_id=customer.c_id where date_format(s_date, '%Y-%m-%d') > '");
					strcat(query, sdate);
					strcat(query, "' and date_format(s_date, '%Y-%m-%d') < '");
					strcat(query, edate);
					strcat(query, "' and supplier.name = '");
					strcat(query, supp);
					strcat(query, "'");
					printf("\n");
				}
				else {
					arg = 0;
					if (op == 0) printf("\n\n");
					else printf("\nwrong input\n\n");
				}

			}
			else if (op == 4) {
				arg = 1;
				char* k = (char*)malloc(sizeof(char) * 5);
				printf("\n\n");
				printf("---- TYPE 4 ----\n\n");
				printf("** Find the top k brands by dollar-amount sold by the year. **\n");
				printf(" Which K? : ");
				scanf("%s", k);
				strcpy(query, "select brand.name from brand left join model on brand.b_id = model.b_id inner join vehicle on model.m_id = vehicle.m_id right join sale on vehicle.VIN = sale.VIN group by brand.name order by sum(price) desc limit ");
				strcat(query, k);
				printf("\n");
			}
			else if (op == 5) {
				arg = 1;
				char* k = (char*)malloc(sizeof(char) * 5);
				printf("\n\n");
				printf("---- TYPE 5 ----\n\n");
				printf("** Find the top k brands by unit sales by the year. **\n");
				printf(" Which K? : ");
				scanf("%s", k);
				strcpy(query, "select brand.name from sale join vehicle on vehicle.VIN = sale.VIN inner join model on model.m_id = vehicle.m_id inner join brand on brand.b_id = model.b_id	group by brand.name	order by count(brand.name) desc limit ");
				strcat(query, k);
				printf("\n");
			}
			else if (op == 6) {
				arg = 1;
				char* k = (char*)malloc(sizeof(char) * 5);
				printf("\n\n");
				printf("---- TYPE 6 ----\n\n");
				printf("** In what month(s) do convertibles sell best? **\n");
				strcpy(query, "select MONTH(date) from sale join vehicle on vehicle.VIN=sale.VIN where body_style='convertible' group by MONTH(date) order by count(sale.VIN) desc limit 1");
				printf("\n");
			}
			else if (op == 7) {
				arg = 1;
				char* k = (char*)malloc(sizeof(char) * 5);
				printf("\n\n");
				printf("---- TYPE 7 ----\n\n");
				printf("** Find those dealers who keep a vehicle in inventory for the longest average time. **\n");
				strcpy(query, "select dealer from vehicle left outer join sale on vehicle.VIN=sale.VIN where date is null group by dealer order by avg(in_date) asc limit 1");
				printf("\n");
			}
			else {
				printf("\nwrong input\n\n");
			}

			if (arg != 0) {
				int state = 0;
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						for (int i = 0; i < arg; i++) {
							printf("%s\t", sql_row[i]);
						}
						printf("\n");
					}
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
		}
		int state = 0;
		state = mysql_query(connection, "drop table brand, company, customer, model, plant, sale, supplier, vehicle");
		mysql_close(connection);
	}
	return 0;
}