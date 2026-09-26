const API_URL = "https://campusrouteoptimizer.onrender.com";


// Get HTML elements

const sourceSelect =
    document.getElementById("source");

const destinationSelect =
    document.getElementById("destination");

const findRouteButton =
    document.getElementById("findRoute");

const swapButton =
    document.getElementById("swapButton");

const resultCard =
    document.getElementById("result");

const routeText =
    document.getElementById("route");

const distanceText =
    document.getElementById("distance");

const roadSourceSelect = document.getElementById("roadSource");
const roadDestinationSelect = document.getElementById("roadDestination");

const blockRoadButton = document.getElementById("blockRoad");
const unblockRoadButton = document.getElementById("unblockRoad");

const roadMessage = document.getElementById("roadMessage");    

const canteenCseEdge =
document.querySelector(".edge-canteen-cse");

// ================================
// LOAD LOCATIONS
// ================================

async function loadLocations() {

    try {

        const response =
            await fetch(`${API_URL}/locations`);

        const locations =
            await response.json();


       locations.forEach(location => {

    const sourceOption = document.createElement("option");
    sourceOption.value = location;
    sourceOption.textContent = location;
    sourceSelect.appendChild(sourceOption);

    const destinationOption = document.createElement("option");
    destinationOption.value = location;
    destinationOption.textContent = location;
    destinationSelect.appendChild(destinationOption);

    const roadSourceOption = document.createElement("option");
    roadSourceOption.value = location;
    roadSourceOption.textContent = location;
    roadSourceSelect.appendChild(roadSourceOption);

    const roadDestinationOption = document.createElement("option");
    roadDestinationOption.value = location;
    roadDestinationOption.textContent = location;
    roadDestinationSelect.appendChild(roadDestinationOption);
});

    }

    catch (error) {

        console.error(
            "Could not connect to backend.",
            error
        );

    }

}


// ================================
// FIND SHORTEST ROUTE
// ================================

findRouteButton.addEventListener(
    "click",
    async () => {

        const source =
            sourceSelect.value;

        const destination =
            destinationSelect.value;


        // Validate selections

        if (!source || !destination) {

            resultCard.classList.remove("hidden");

            routeText.innerHTML =
                "Please select both locations.";

            distanceText.textContent = "--";

            return;

        }


        // Same location

        if (source === destination) {

            resultCard.classList.remove("hidden");

            routeText.innerHTML =
                "Source and destination cannot be the same.";

            distanceText.textContent = "--";

            return;

        }


        try {

            const response =
                await fetch(
                    `${API_URL}/route?source=${encodeURIComponent(source)}&destination=${encodeURIComponent(destination)}`
                );


            const data =
                await response.json();


            // No route

            if (!data.found) {

                resultCard.classList.remove("hidden");

                routeText.innerHTML =
                    "No available route found.";

                distanceText.textContent = "--";

                return;

            }


            // Show result

            resultCard.classList.remove("hidden");


            // Create visual route

            routeText.innerHTML =
                data.path
                    .map(
                        (location, index) => {

                            const node =
                                `<span class="route-node">${location}</span>`;

                            if (
                                index ===
                                data.path.length - 1
                            ) {

                                return node;

                            }

                            return node +
                                `<span class="route-arrow">→</span>`;

                        }
                    )
                    .join("");


            distanceText.textContent =
                data.distance + " km";


        }

        catch (error) {

            console.error(error);

            resultCard.classList.remove("hidden");

            routeText.innerHTML =
                "Could not connect to the backend.";

            distanceText.textContent = "--";

        }

    }
);


// ================================
// SWAP LOCATIONS
// ================================

swapButton.addEventListener(
    "click",
    () => {

        const source =
            sourceSelect.value;

        const destination =
            destinationSelect.value;


        sourceSelect.value =
            destination;

        destinationSelect.value =
            source;

    }
);


// ================================
// INITIALIZE
// ================================

loadLocations();

// ================================
// UPDATE ROAD STATUS
// ================================

async function updateRoad(action) {

    const source = roadSourceSelect.value;
    const destination = roadDestinationSelect.value;

    if (!source || !destination) {

        roadMessage.textContent =
            "Please select both locations.";

        return;
    }

    if (source === destination) {

        roadMessage.textContent =
            "Road locations cannot be the same.";

        return;
    }

    roadMessage.textContent =
        action === "block"
            ? "Blocking road..."
            : "Opening road...";

    try {

        const response = await fetch(
            `${API_URL}/${action}?source=${encodeURIComponent(source)}&destination=${encodeURIComponent(destination)}`,
            {
                method: "POST"
            }
        );

        const data = await response.json();

        roadMessage.textContent =
            data.message || "Road updated successfully.";

        // Update the visual campus network
        updateGraphRoad(
            source,
            destination,
            action === "block"
        );

    }
    catch (error) {

        console.error(error);

        roadMessage.textContent =
            "Could not connect to the backend.";

    }
}


// ================================
// BLOCK ROAD BUTTON
// ================================

blockRoadButton.addEventListener(
    "click",
    () => {
        updateRoad("block");
    }
);


// ================================
// UNBLOCK ROAD BUTTON
// ================================

unblockRoadButton.addEventListener(
    "click",
    () => {
        updateRoad("unblock");
    }
);


// ================================
// UPDATE GRAPH ROAD
// ================================

function updateGraphRoad(
    source,
    destination,
    blocked
) {

    const graphEdges =
        document.querySelectorAll(".graph-edge");

    graphEdges.forEach(edge => {

        const edgeFrom =
            edge.dataset.from;

        const edgeTo =
            edge.dataset.to;


        // Roads work in both directions.
        // Canteen -> CSE and CSE -> Canteen
        // represent the same physical road.

        const sameRoad =
            (
                edgeFrom === source &&
                edgeTo === destination
            )
            ||
            (
                edgeFrom === destination &&
                edgeTo === source
            );


        if (sameRoad) {

            if (blocked) {

                edge.classList.add(
                    "blocked-road"
                );

            }
            else {

                edge.classList.remove(
                    "blocked-road"
                );

            }

        }

    });
}
