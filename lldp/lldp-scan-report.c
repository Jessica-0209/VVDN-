#include <stdio.h>
#include <lldpctl.h>

int main() {
    lldpctl_conn_t *conn = lldpctl_new(NULL, NULL, NULL);
    if (!conn) {
        fprintf(stderr, "Failed to connect to lldpd\n");
        return 1;
    }

    lldpctl_atom_t *interfaces = lldpctl_get_interfaces(conn);
    if (!interfaces) {
        fprintf(stderr, "No interfaces found.\n");
        lldpctl_release(conn);
        return 1;
    }

    lldpctl_atom_t *iface;
    lldpctl_atom_foreach(interfaces, iface) {
        const char *ifname = lldpctl_atom_get_str(iface, lldpctl_k_interface_name);
        printf("Interface: %s\n", ifname ? ifname : "N/A");

        // Use the correct constant here
        lldpctl_atom_t *neighbors = lldpctl_atom_get(iface, lldpctl_k_port_neighbors);
        if (!neighbors) {
            printf("  No neighbors found.\n");
            continue;
        }

        lldpctl_atom_t *neighbor;
        lldpctl_atom_foreach(neighbors, neighbor) {
            const char *chassis_name = lldpctl_atom_get_str(neighbor, lldpctl_k_chassis_name);
            const char *port_id = lldpctl_atom_get_str(neighbor, lldpctl_k_port_id);
            const char *port_descr = lldpctl_atom_get_str(neighbor, lldpctl_k_port_descr);

            printf("  Neighbor:\n");
            printf("    Chassis Name: %s\n", chassis_name ? chassis_name : "N/A");
            printf("    Port ID:      %s\n", port_id ? port_id : "N/A");
            printf("    Port Desc:    %s\n", port_descr ? port_descr : "N/A");
            printf("  -------------------------\n");
        }
        lldpctl_atom_dec_ref(neighbors);
    }

    lldpctl_atom_dec_ref(interfaces);
    lldpctl_release(conn);
    return 0;
}

