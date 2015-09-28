<?php

/****
 * Local entities
 *
 * Locations, Services, Service Areas
 *
 * Location:
 * - Name (The name of the location. "White Fox Studios - Asheville, NC Sales Office")
 * - Address (The location address. Also renders a map)
 * - Phone (The primary phone of this location)
 * - Email (The primary email of this location)
 * - Description (A long description, describing in detail the location)
 * - Hours (The hours of operation for this location)
 * - Services: (Entity reference list of services provided at this location)
 *   - Name (The name of the service)
 *   - Description (A long, detailed description of the service)
 *   - Photos (One or more photos that visually represent the service)
 *   - Sub Services (Entity reference list of services provided as part of this service)
 *   - Related Services (List of services that referenced this service)
 *   - Areas (List of areas that referenced this service)
 *   - Locations (List of locations that referenced this service)
 * - Service Areas:
 *   - Name (The name of the area)
 *   - Locations (List of locations that referenced this area)
 *   - Services (Entity reference list of services provided in this area)
 *   - Description (A long, detailed description of the business in this area)
 *   - Area Info (A cited summary of the area with links)
 *   - Area Photo (One or more photos that visually represent the service)
 *   - Area Map (embed.ly map embed code, just paste the whole thing)
 *   - Social Networks (Links to social networking profiles specific to this area)
 * - Photos (One or more photos that visually represent the location)
 * - Reviews (Find the G+ review, share it, paste the shared post's embed code)
 * - Social Networks (Links to social networking profiles specific to this location)
****/

